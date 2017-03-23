#include "parser.hpp"
#include <string>
#include <algorithm>

Parser::Parser(){


}

Parser::~Parser(){


}




// Recursively print AST to standard out
void Parser::show_tree( Tree_Node *root_node, string prefix ){

    // print node information: type, specifier, sValue, nValue, rename
    char indent[] = "-";
    cout << prefix << "Node type: "      << std::to_string(root_node->nodeType)      << endl;
    cout << prefix << "Type Specifier: " << std::to_string(root_node->typeSpecifier) << endl;
    cout << prefix << "sValue: "         << root_node->sValue                        << endl;
    cout << prefix << "nValue: "         << root_node->nValue                        << endl;
    cout << prefix << "rename: "         << root_node->rename                        << endl;

    // print child 1 (C1) if not null
    if (root_node->C1 != NULL){
        cout << prefix << "C1:";
        show_tree(root_node->C1, (prefix + indent));
    }

    // print child 2 (C2) if not null
    if (root_node->C2 != NULL){
        cout << prefix << "C2:";
        show_tree(root_node->C2, (prefix + indent));
    }

    // print child 3 (C3) if not null
    if (root_node->sibling != NULL){
        show_tree(root_node->sibling, prefix);
    }

}




void Parser::find_siblings( Tree_Node *root_node, vector<Token*> token_list ){

    // while token_list is not EMPTY
    cout << "find_siblings" << endl;
    while( !token_list.empty() )
    {
        Tree_Node *node = new Tree_Node();

        // pop first_token off of token_list and switch on its type
        Token *first_token = new Token(token_list.front()->type,token_list.front()->value);
        token_list.erase( token_list.begin() );

        switch( first_token->type )
        {

            case EOF:
                cout << "find_siblings - case EOF" << endl;
                token_list.clear();
                break;

            case COMMA:
            case RBRACKET:
            case RBRACE:
            case SEMI:
            {
                cout << "find_siblings - case COMMA|RBRACKET|RBRACE|SEMI" << endl;
                break;
            }

            case INT:
            {
                cout << "find_siblings - case INT" << endl;
                node->nodeType = VARIABLE;
                node->typeSpecifier = INT;
            }

            case VOID:
            {
                cout << "find_siblings - case VOID" << endl;
                node->typeSpecifier = first_token->type;
                if( !token_list.empty() )
                {
                    // pop second_token off of token_list and switch on its type
                    cout << "Tokenlist size: " << token_list.size() << endl;
                    cout << "Token type: " << token_list.at(45) << endl;
                    cout << "Token value: " << token_list.front() << endl;
                    Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                    cout << "Erasing\n";
                    token_list.erase( token_list.begin() );
                    cout << "\t\tSwitch\n" << second_token->type << "^^^\n";
                    switch( second_token->type )
                    {

                        case ID:
                        {
                            cout << "find_siblings - case VOID - case ID" << endl;
                            node->sValue = second_token->value;
                            cout << "Got second token\n";
                            if( !token_list.empty() )
                            {
                                cout << "\t\tToken list not empty\n";
                                // pop third_token off of token_list and switch on its type
                                Token *third_token = new Token(token_list.front()->type,token_list.front()->value);
                                token_list.erase( token_list.begin() );
                                switch( third_token->type )
                                {

                                    case LBRACKET:
                                    {
                                        cout << "find_siblings - case VOID - case ID - case LBRACKET" << endl;
                                        // pop fourth_token off of token_list and switch on its type
                                        node->nodeType = ARRAY;
                                        Token *fourth_token = new Token(token_list.front()->type,token_list.front()->value);
                                        token_list.erase( token_list.begin() );
                                        switch( fourth_token->type )
                                        {

                                            case NUMBER:
                                            {
                                                cout << "find_siblings - case VOID - case ID - case LBRACKET - case NUMBER" << endl;
                                                node->nValue = std::stoi( fourth_token->value );
                                                break;
                                            }

                                            case RBRACKET:
                                            {
                                                cout << "find_siblings - case VOID - case ID - case LBRACKET - case RBRACKET" << endl;
                                                break;
                                            }

                                            default:
                                            {
                                              cerr << "ERROR: Unhandled fourth_token type: " << fourth_token->value << endl;
                                              exit(-1);
                                            }
                                        }
                                        // set sibling pointer without replacing sibling
                                        root_node->sibling = node;
                                        root_node = node;
                                        break;
                                    }
                                    // LPAREN ->
                                    case LPAREN:
                                    {
                                        cout << "find_siblings - case VOID - case ID - case LPAREN" << endl;
                                        // LPAREN means we are declaring a function
                                        node->nodeType = FUNCTION;
                                        node->C1 = new Tree_Node();
                                        node->C1->nodeType = PARAMETER_LIST;
                                        // Get iterator pointing to first instance of RPAREN
                                        vector<Token*>::iterator right_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                                        if ( right_paren == token_list.end())
                                        {
                                            node->C1->typeSpecifier = VOID;
                                        }
                                        else
                                        {
                                            node->C1->typeSpecifier = INT;
                                            vector<Token*> passed_list;
                                            int start, end;
                                            start = std::distance(token_list.begin(),token_list.begin());
                                            end = std::distance(token_list.begin(), right_paren);
                                            for (int i = start; i < end; ++i){
                                                passed_list.push_back(NULL);
                                            }
                                            std::move( token_list.begin(), right_paren, passed_list.begin() );
                                            
                                            build_subtree( node->C1, passed_list );
                                            
                                        }
                                        node->C2 = new Tree_Node();
                                        node->C2->nodeType = COMPOUND;
                                        // Get iterator pointing to first instance of LBRACE
                                        vector<Token*>::iterator open_brace = std::find_if( token_list.begin(), token_list.end(), IS_LBRACE );

                                        int num_of_open_braces = 1;
                                        int num_of_closed_braces = 0;
                                        vector<Token*>::iterator close_brace;
                                        vector<Token*>::iterator index = open_brace;
                                        // cout << "Top of token list: " << token_list.front()->value << endl;
                                        // token_list.erase(token_list.begin());
                                        // cout << "Top of token list AGAIN: " << token_list.front()->value << endl;
                                        do
                                        {
                                            index += 1;
                                            int position = std::distance( token_list.begin(), index );
                                            if( position == token_list.size() )
                                            {
                                                cerr << "ERROR: Parenthesis mismatch" << endl;
                                                exit(-1);
                                            }
                                            Token *token = new Token(token_list.at( position )->type,token_list.at( position )->value);
                                            switch( token->type )
                                            {
                                                case LBRACE:
                                                {
                                                    cout << "find_siblings - case VOID - case ID - case LPAREN - case LBRACE" << endl;
                                                    num_of_open_braces += 1;
                                                    break;
                                                }

                                                case RBRACE:
                                                {
                                                    cout << "find_siblings - case VOID - case ID - case LPAREN - case LBRACE" << endl;
                                                    num_of_closed_braces += 1;
                                                    break;
                                                }

                                                default:
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        while ( num_of_open_braces != num_of_closed_braces );
                                        close_brace = index;
                                        // skip the opening brace {
                                        open_brace += 1;

                                        vector<Token*> passed_list;
                                        int start, end;
                                        start = std::distance(token_list.begin(),open_brace);
                                        end = std::distance(token_list.begin(), close_brace);
                                        for (int i = start; i < end; ++i){
                                            passed_list.push_back(NULL);
                                        }
                                        std::move( open_brace, close_brace, passed_list.begin() );
                                        build_subtree( node->C2, passed_list );
                                        root_node->sibling = node;
                                        root_node = node;
                                        break;
                                    }

                                    case RPAREN:
                                    case COMMA:
                                    case SEMI:
                                    {
                                        cout << "find_siblings - case VOID - case ID - case RPAREN|COMMA|SEMI" << endl;
                                        root_node->sibling = node;
                                        root_node = node;
                                        break;
                                    }

                                    default:
                                    {
                                        cerr << "ERROR: Unhandled third_token type: " << third_token->value << endl;
                                        exit(-1);
                                    }
                                }
                            }
                            else
                            {
                                cout << "Token list was empty\n";
                                root_node->sibling = node;
                                root_node = node;
                                cout << "Assigned!\n";
                            }
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }

            case ID:
            {
                cout << "find_siblings - case ID" << endl;
                break;
            }

            default:
            {
                cerr << "ERROR: Unhandled first_token type: " << first_token->value << endl;
                exit(-1);
            }
        }
    }
}




void Parser::find_arguments(Tree_Node *root_node, vector<Token*> token_list ){

    cout << "find_arguments" << endl;
    while( !token_list.empty() )
    {
        Tree_Node *node;
        Token *first_token = new Token(token_list.front()->type,token_list.front()->value);
        token_list.erase( token_list.begin() );
        switch( first_token->type )
        {

            case NUMBER:
            {
                cout << "find_arguments - case NUMBER" << endl;
                if( token_list.empty() )
                {
                    node->nodeType = NUMBER;
                    node->typeSpecifier = INT;
                    node->nValue = std::stoi( first_token->value );
                }
                else
                {
                    Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                    token_list.erase( token_list.begin() );
                    switch( second_token->type )
                    {

                        case COMMA:
                        {
                            cout << "find_arguments - case NUMBER - case COMMA" << endl;
                            node->nodeType = NUMBER;
                            node->typeSpecifier = INT;
                            node->nValue = std::stoi( first_token->value );
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }

            case ID:
            {
                cout << "find_arguments - case ID" << endl;
                if( token_list.empty() )
                {
                    node->nodeType = VARIABLE;
                    node->sValue = first_token->value;
                }
                else
                {
                    Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                    token_list.erase( token_list.begin() );
                    switch( second_token->type )
                    {
                        case COMMA:
                        {
                            node->nodeType = VARIABLE;
                            node->sValue = first_token->value;
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }
            default:
            {
                cerr << "ERROR: Unhandled first_token type: " << first_token->value << endl;
                exit(-1);
            }
        }
        root_node->sibling = node;
        root_node = node;
    }
}



void Parser::find_expression(Token *first_token, Tree_Node *root_node, vector<Token*> token_list ){

    cout << "find_expression" << endl;
    Tree_Node *node = new Tree_Node();
    while( !token_list.empty() )
    {
        if( first_token == NULL )
        {
            Token *first_token = new Token(token_list.front()->type,token_list.front()->value);
            token_list.erase( token_list.begin() );
        }


        node->nodeType = EXPRESSION;
        node->C1 = new Tree_Node();
        node->C1->sValue = first_token->value;
        switch( first_token->type )
        {

            case NUMBER:
            {
                cout << "find_expression - case NUMBER" << endl;
                node->C1->nodeType = NUMBER;
                node->C1->typeSpecifier = INT;
                node->C1->nValue = std::stoi( first_token->value );
                break;
            }

            case ID:
                cout << "find_expression - case ID" << endl;
                node->C1->nodeType = VARIABLE;
                if( !token_list.empty() )
                {
                    Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                    token_list.erase( token_list.begin() );
                    switch( second_token->type )
                    {

                        case LBRACKET:
                        {
                            cout << "find_expression - case NUMBER - case LBRACKET" << endl;
                            node->C1->nodeType = ARRAY;
                            Token *third_token = new Token(token_list.front()->type,token_list.front()->value);
                            token_list.erase( token_list.begin() );
                            switch( third_token->type )
                            {

                                case INT:
                                {
                                    cout << "find_expression - case NUMBER - case LBRACKET - case INT" << endl;
                                    node->C1->nValue = std::stoi( third_token->value );
                                    token_list.erase( token_list.begin() );
                                    break;
                                }

                                case ID:
                                {
                                    cout << "find_expression - case NUMBER - case LBRACKET - case ID" << endl;
                                    vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_SEMI );
                                    vector<Token*> passed_list;
                                    int start, end;
                                    start = std::distance(token_list.begin(),token_list.begin() + 1);
                                    end = std::distance(token_list.begin(), index);
                                    for (int i = start; i < end; ++i){
                                        passed_list.push_back(NULL);
                                    }
                                    std::move( (token_list.begin() + 1), index, passed_list.begin() );
                                    find_expression( third_token, node->C1, passed_list);
                                    token_list.erase( token_list.begin() );
                                    node->C1 = node->C1->sibling;
                                    break;
                                }

                                default:
                                {
                                    cerr << "ERROR: Unhandled third_token type: " << third_token->value << endl;
                                    exit(-1);
                                }
                            }
                            break;
                        }

                        case MINUS:
                        {
                            cout << "find_expression - case NUMBER - case MINUS" << endl;
                            node->nodeType = MINUS;
                            node->C2 = new Tree_Node();
                            vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_MINUS );
                            find_expression(NULL, node->C2, token_list);
                            token_list.erase( token_list.begin(), index );
                            node->C2 = node->C2->sibling;
                            break;
                        }

                        case LS:
                        {
                            cout << "find_expression - case NUMBER - case LS" << endl;
                            node->nodeType = LS;
                            node->C2 = new Tree_Node();
                            vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_SEMI );
                            find_expression(NULL, node->C2, token_list);
                            token_list.erase( token_list.begin(), index );
                            node->C2 = node->C2->sibling;
                            break;
                        }

                        case ASSIGN:
                        {
                            cout << "find_expression - case NUMBER - case ASSIGN" << endl;
                            Token *third_token = new Token(token_list.front()->type,token_list.front()->value);
                            token_list.erase( token_list.begin() );
                            switch( third_token->type )
                            {

                                case NUMBER:
                                {
                                    cout << "find_expression - case NUMBER - case ASSIGN - case NUMBER" << endl;
                                    node->nodeType = ASSIGN;
                                    node->C2 = new Tree_Node();
                                    node->C2->nodeType = NUMBER;
                                    node->C2->typeSpecifier = INT;
                                    node->C2->nValue = stoi( third_token->value );
                                    break;
                                }

                                case ID:
                                {
                                    cout << "find_expression - case NUMBER - case ASSIGN - case ID" << endl;
                                    node->C2 = new Tree_Node();
                                    if ( token_list.empty() )
                                    {
                                        node->C2->nodeType = VARIABLE;
                                        node->C2->sValue = third_token->value;
                                    }
                                    else
                                    {
                                        Token *fourth_token = new Token(token_list.front()->type,token_list.front()->value);
                                        token_list.erase( token_list.begin() );
                                        switch( fourth_token->type )
                                        {

                                            case LPAREN:
                                            {
                                                cout << "find_expression - case NUMBER - case ASSIGN - case ID - case LPAREN" << endl;
                                                node->C2->nodeType = CALL;
                                                node->C2->sValue = third_token->value;
                                                node->C2->typeSpecifier = INT;
                                                node->C2->C1 = new Tree_Node();
                                                node->C2->C1->nodeType = ARGUMENTS;
                                                vector<Token*>::iterator right_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                                                vector<Token*> passed_list;
                                                int start, end;
                                                start = std::distance(token_list.begin(),token_list.begin());
                                                end = std::distance(token_list.begin(), right_paren);
                                                for (int i = start; i < end; ++i){
                                                    passed_list.push_back(NULL);
                                                }
                                                std::move( token_list.begin(), right_paren, passed_list.begin() );
                                                find_arguments(node->C2->C1, passed_list);
                                                break;
                                            }

                                            case SEMI:
                                            {
                                                cout << "find_expression - case NUMBER - case ASSIGN - case ID - case SEMI" << endl;
                                                node->C2->nodeType = VARIABLE;
                                                node->C2->sValue = third_token->value;
                                                break;
                                            }

                                            case LBRACKET:
                                            {
                                                cout << "find_expression - case NUMBER - case ASSIGN - case ID - case LBRACKET" << endl;
                                                node->C2->nodeType = ARRAY;
                                                node->C2->sValue = third_token->value;
                                                node->C2->C1 = new Tree_Node();
                                                vector<Token*>::iterator right_bracket = std::find_if( token_list.begin(), token_list.end(), IS_RBRACKET );
                                                vector<Token*> passed_list;
                                                int start, end;
                                                start = std::distance(token_list.begin(),token_list.begin());
                                                end = std::distance(token_list.begin(), right_bracket);
                                                for (int i = start; i < end; ++i){
                                                    passed_list.push_back(NULL);
                                                }
                                                std::move( token_list.begin(), right_bracket, passed_list.begin() );
                                                find_expression( NULL, node->C2->C1, passed_list );
                                                node->C2->C1 = node->C2->C1->sibling;
                                                break;
                                            }

                                            case PLUS:
                                            {
                                                cout << "find_expression - case NUMBER - case ASSIGN - case ID - case PLUS" << endl;
                                                node->C2->nodeType = PLUS;
                                                node->C2->C1 = node;
                                                Tree_Node *temp_node = node->C2;
                                                node->C2 = NULL;
                                                node->C2 = new Tree_Node();
                                                vector<Token*>::iterator index = token_list.end();
                                                vector<Token*> passed_list;
                                                int start, end;
                                                start = std::distance(token_list.begin(),token_list.begin());
                                                end = std::distance(token_list.begin(), index);
                                                for (int i = start; i < end; ++i){
                                                    passed_list.push_back(NULL);
                                                }
                                                std::move( token_list.begin(), index, passed_list.begin() );
                                                find_expression(NULL, node->C2, passed_list);
                                                node->C2 = node->C2->sibling;
                                                if( node->C1->typeSpecifier == EXPRESSION && node->C1->C1 != NULL && node->C1->C2 == NULL)
                                                {
                                                    node->C1 = node->C1->C1;
                                                }
                                                if( node->C2->typeSpecifier == EXPRESSION && node->C2->C1 != NULL && node->C2->C2 == NULL)
                                                {
                                                    node->C2 = node->C2->C1;
                                                }
                                                break;
                                            }

                                            default:
                                            {
                                               cerr << "ERROR: Unhandled fourth_token type: " << fourth_token->value << endl;
                                               exit(-1);
                                            }
                                        }
                                    }
                                    break;
                                }

                                default:
                                {
                                   cerr << "ERROR: Unhandled third_token type: " << third_token->value << endl;
                                   exit(-1);
                                }
                            }
                            break;
                        }

                        default:
                        {
                           cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                           exit(-1);
                        }
                    }
                }
                // break;
                default:
                {
                    cerr << "ERROR: Unhandled first_token type: " << first_token->value << endl;
                    exit(-1);
                }
            }


        }

        while( !token_list.empty() && ( token_list.at(0)->type == SEMI ) )
        {
            token_list.erase( token_list.begin() );
        }

        root_node->sibling = node;
        root_node = node;
        first_token = NULL;
    //}
}



void Parser::find_statement_list_siblings(Tree_Node *root_node, vector<Token*> token_list ){

    cout << "find_statement_list_siblings" << endl;
    while( !token_list.empty() )
    {
        Tree_Node *node = new Tree_Node();
        Token *first_token = new Token(token_list.front()->type,token_list.front()->value);
        token_list.erase( token_list.begin() );
        switch( first_token->type )
        {

            case WRITE:
            {
                cout << "find_statement_list_siblings - case WRITE" << endl;
                node->nodeType = WRITE;
                vector<Token*>::iterator close_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin()+1);
                end = std::distance(token_list.begin(), close_paren);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( (token_list.begin() + 1), close_paren, passed_list.begin() );
                node->C1 = new Tree_Node();
                node->C1->nodeType = EXPRESSION;
                find_expression( NULL, node->C1, passed_list);
                token_list.erase( token_list.begin() );
                break;
            }

            case READ:
            {
                cout << "find_statement_list_siblings - case READ" << endl;
                node->nodeType = READ;
                Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                token_list.erase( token_list.begin() );
                switch( second_token->type )
                {

                    case ID:
                    {
                        cout << "find_statement_list_siblings - case READ - case ID" << endl;
                        Token *third_token = new Token(token_list.front()->type,token_list.front()->value);
                        token_list.erase( token_list.begin() );
                        node->C1 = new Tree_Node();
                        switch( third_token->type )
                        {

                            case ID:
                            {
                                cout << "find_statement_list_siblings - case READ - case ID - case ID" << endl;
                                node->C1->nodeType = VARIABLE;
                                node->C1->nValue = std::stoi( second_token->value );
                                break;
                            }

                            case LBRACKET:
                            {
                                cout << "find_statement_list_siblings - case READ - case ID - case ID" << endl;
                                node->C1->nodeType = ARRAY;
                                node->C1->sValue = second_token->value;
                                vector<Token*>::iterator close_bracket = std::find_if( token_list.begin(), token_list.end(), IS_RBRACKET );
                                vector<Token*> passed_list;
                                int start, end;
                                start = std::distance(token_list.begin(),close_bracket + 1);
                                end = std::distance(token_list.begin(), token_list.end());
                                for (int i = start; i < end; ++i){
                                    passed_list.push_back(NULL);
                                }
                                std::move( (close_bracket + 1), token_list.end(), passed_list.begin() );
                                token_list.erase( token_list.begin() );
                                break;
                            }

                            default:
                            {
                                cerr << "ERROR: Unhandled third_token type: " << third_token->value << endl;
                                exit(-1);
                            }
                        }
                        break;
                    }

                    default:
                    {
                        cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                        exit(-1);
                    }
                }
                break;
            }

            case INT:
            {
                cout << "find_statement_list_siblings - case INT" << endl;
                vector<Token*> new_token_list;
                new_token_list.insert( new_token_list.begin(), first_token );
                std::copy( token_list.begin(), token_list.end(), (new_token_list.begin() + 1) );
                node->nodeType = COMPOUND;
                vector<Token*>::iterator close_brace = std::find_if( new_token_list.begin(), new_token_list.end(), IS_RBRACE );
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin());
                end = std::distance(token_list.begin(), close_brace);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( new_token_list.begin(), close_brace, passed_list.begin() );
                build_subtree( node, new_token_list );
                token_list = new_token_list;
                break;
            }

            case RETURN:
            {
                cout << "find_statement_list_siblings - case RETURN" << endl;
                node->nodeType = RETURN;
                node->C1 = new Tree_Node();
                vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_SEMI );
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin());
                end = std::distance(token_list.begin(), index);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin(), index, passed_list.begin() );
                find_expression( NULL, node->C1, passed_list );
                node->C1 = node->C1->sibling;
                break;
            }

            case IF:
            {
                cout << "find_statement_list_siblings - case IF" << endl;
                node->nodeType = IF;
                node->C1 = new Tree_Node();
                vector<Token*>::iterator close_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin() + 1);
                end = std::distance(token_list.begin(), close_paren);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin() + 1, close_paren, passed_list.begin() );
                token_list.erase( token_list.begin() );
                node->C1 = node->C1->sibling;

                node->C2 = new Tree_Node();
                node->C2->nodeType = COMPOUND;
                vector<Token*>::iterator close_brace = std::find_if( token_list.begin(), token_list.end(), IS_RBRACE );
                passed_list.clear();
                start = std::distance(token_list.begin(),token_list.begin() + 1);
                end = std::distance(token_list.begin(), close_brace);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin() + 1, close_brace, passed_list.begin() );
                token_list.erase( token_list.begin() );
                build_subtree( node->C2, passed_list );

                node->C3 = new Tree_Node();
                node->C3->nodeType = COMPOUND;
                close_brace = std::find_if( token_list.begin(), token_list.end(), IS_RBRACE );
                passed_list.clear();
                start = std::distance(token_list.begin(),token_list.begin() + 1);
                end = std::distance(token_list.begin(), close_brace);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin() + 1, close_brace, passed_list.begin() );
                token_list.erase( token_list.begin() );
                build_subtree( node->C3, passed_list);

                break;
            }

            case ID:
            {
                cout << "find_statement_list_siblings - case ID" << endl;
                Token *second_token = new Token(token_list.front()->type,token_list.front()->value);
                token_list.erase( token_list.begin() );
                switch( second_token->type )
                {
                    case LBRACKET:
                    {
                        cout << "find_statement_list_siblings - case ID - case LBRACKET" << endl;
                        node->nodeType = EXPRESSION;
                        vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_SEMI );
                        vector<Token*> passed_list;
                        int start, end;
                        start = std::distance(token_list.begin(),token_list.begin());
                        end = std::distance(token_list.begin(), index);
                        for (int i = start; i < end; ++i){
                            passed_list.push_back(NULL);
                        }
                        std::move( token_list.begin(), index, passed_list.begin() );
                        find_expression( first_token, node, passed_list);
                        break;
                    }

                    case ASSIGN:
                    {
                        cout << "find_statement_list_siblings - case ID - case ASSIGN" << endl;
                        node->nodeType = ASSIGN;
                        node->C1 = new Tree_Node();
                        node->C1->nodeType = VARIABLE;
                        node->C1->sValue = first_token->value;

                        node->C2 = new Tree_Node();
                        vector<Token*>::iterator index = std::find_if( token_list.begin(), token_list.end(), IS_SEMI );
                        vector<Token*> passed_list;
                        int start, end;
                        start = std::distance(token_list.begin(),token_list.begin());
                        end = std::distance(token_list.begin(), index);
                        for (int i = start; i < end; ++i){
                            passed_list.push_back(NULL);
                        }
                        std::move( token_list.begin(), index, passed_list.begin() );
                        node->C2 = node->C2->sibling;
                        break;
                    }

                    case LPAREN:
                    {
                        cout << "find_statement_list_siblings - case ID - case LPAREN" << endl;
                        token_list.erase( token_list.begin() );
                        node->nodeType = CALL;
                        node->sValue = first_token->value;
                        node->C1 = new Tree_Node();
                        node->C1->nodeType = ARGUMENTS;

                        vector<Token*>::iterator close_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                        vector<Token*> passed_list;
                        int start, end;
                        start = std::distance(token_list.begin(),token_list.begin());
                        end = std::distance(token_list.begin(), close_paren);
                        for (int i = start; i < end; ++i){
                            passed_list.push_back(NULL);
                        }
                        std::move( token_list.begin(), close_paren, passed_list.begin() );
                        find_arguments( node->C1, passed_list);
                        break;
                    }

                    default:
                    {
                        cerr << "ERROR: Unhandled second_token type: " << second_token->value << endl;
                        exit(-1);
                    }
                }
                break;
            }

            case CALL:
            {

                cout << "find_statement_list_siblings - case CALL" << endl;
                node->nodeType = CALL;
                break;
            }

            case WHILE:
            {
                cout << "find_statement_list_siblings - case WHILE" << endl;
                node->nodeType = WHILE;
                node->C1 = new Tree_Node();
                node->C1->nodeType = EXPRESSION;
                vector<Token*>::iterator close_paren = std::find_if( token_list.begin(), token_list.end(), IS_RPAREN );
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin() + 1);
                end = std::distance(token_list.begin(), close_paren);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin() + 1, close_paren, passed_list.begin() );
                token_list.erase( token_list.begin() );
                find_expression( NULL, node->C1, passed_list);

                node->C1 = node->C1->sibling;
                node->C2 = new Tree_Node();
                node->C2->nodeType = STATEMENT_LIST;
                vector<Token*>::iterator open_brace = std::find_if( token_list.begin(), token_list.end(), IS_LBRACE );
                vector<Token*>::iterator close_brace;
                vector<Token*>::iterator index;

                // find matching braces
                int num_of_open_braces = 1;
                int num_of_closed_braces = 0;
                int position;
                index = open_brace;
                do
                {
                    std::advance( index, 1 );
                    position = std::distance( token_list.begin(), index );
                    Token *token = new Token(token_list.at( position )->type,token_list.at( position )->value);
                    switch ( token->type )
                    {

                        case LBRACE:
                        {
                            cout << "find_statement_list_siblings - case WHILE - case LBRACE" << endl;
                            num_of_open_braces++;
                            break;
                        }

                        case RBRACE:
                        {
                            cout << "find_statement_list_siblings - case WHILE - case RBRACE" << endl;
                            num_of_closed_braces++;
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }
                }
                while( num_of_open_braces != num_of_closed_braces );

                close_brace = index;
                std::advance( open_brace, 1 );
                passed_list.clear();
                start = std::distance(token_list.begin(),open_brace);
                end = std::distance(token_list.begin(), close_brace);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( open_brace, close_brace, passed_list.begin() );
                token_list.erase( token_list.begin(), open_brace );
                build_subtree( node->C2, passed_list);
                break;
            }

            default:
            {
                cerr << "ERROR: Unhandled first_token type: " << first_token->value << endl;
                exit(-1);
            }
        }

        // while token_list is not EMPTY and the next token is SEMI
        while( !token_list.empty() && ((token_list.at(0))->type == SEMI) )
        {
            token_list.erase( token_list.begin() );
        }

        root_node->sibling = node;
        root_node = node;
    }
}




void Parser::build_subtree(Tree_Node *root_node, vector<Token*> token_list ){

    cout << "build_subtree" << endl;
    cout << "Root node: " << root_node->nodeType << endl;
    cout << "Top of token list (subtree): " << token_list.front()->value << endl;
    switch( root_node->nodeType )
    {

        case PROGRAM:
        {
            cout << "build_subtree - case PROGRAM" << endl;
            find_siblings( root_node, token_list);
            break;
        }

        case PARAMETER_LIST:
        {
            cout << "build_subtree - case PARAMETER_LIST" << endl;
            Tree_Node *node;
            node = root_node;
            switch( node->typeSpecifier )
            {
                case VOID:
                {
                    cout << "build_subtree - case PARAMETER_LIST - case VOID" << endl;
                    break;
                }

                case INT:
                {
                    cout << "build_subtree - case PARAMETER_LIST - case VOID" << endl;
                    find_siblings( node, token_list );
                    break;
                }

                default:
                {
                    cerr << "ERROR: Unhandled node typeSpecifier: " << node->typeSpecifier << endl;
                    exit(-1);
                }
            }
        }

        case COMPOUND:
        {
            cout << "build_subtree - case COMPOUND" << endl;
            root_node->C1 = new Tree_Node();
            root_node->C1->nodeType = DECLARATION;
            bool keep_going = true;
            vector<Token*>::iterator index = token_list.begin();
            int position;
            do
            {
                position = std::distance( token_list.begin(), index );
                Token *token = new Token(token_list.at( position )->type,token_list.at( position )->value);
                switch ( token->type )
                {
                    case INT:
                    {
                        cout << "build_subtree - case COMPOUND - case INT" << endl;
                        // assume declarations of form "int i" and not "int i = 0;"
                        std::advance( index, 3 );
                        break;
                    }

                    default:
                    {
                        keep_going = false;
                        break;
                    }
                }
            }
            while( keep_going );

            if( index != token_list.begin() )
            {
                vector<Token*> passed_list;
                int start, end;
                start = std::distance(token_list.begin(),token_list.begin());
                end = std::distance(token_list.begin(), index);
                for (int i = start; i < end; ++i){
                    passed_list.push_back(NULL);
                }
                std::move( token_list.begin(), index, passed_list.begin() );
                find_siblings( root_node->C1, passed_list);
            }

            root_node->C2 = new Tree_Node();
            root_node->C2->nodeType = STATEMENT_LIST;
            build_subtree( root_node->C2, token_list );
            break;
        }

        case STATEMENT_LIST:
        {
            cout << "build_subtree - case STATEMENT_LIST" << endl;
            find_statement_list_siblings( root_node, token_list );
            break;
        }

        default:
        {
            cerr << "ERROR: Unhandled root_node nodeType: " << root_node->nodeType << endl;
            exit(-1);
        }
    }
}

bool IS_RPAREN(Token *t){
    return (t->type == RPAREN);
}
bool IS_LBRACE(Token *t){
    return (t->type == LBRACE);
}
bool IS_RBRACE(Token *t){
    return (t->type == RBRACE);
}
bool IS_SEMI(Token *t){
    return (t->type == SEMI);
}
bool IS_MINUS(Token *t){
    return (t->type == MINUS);
}
bool IS_RBRACKET(Token *t){
    return (t->type == RBRACKET);
}
