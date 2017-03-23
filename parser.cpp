#include "parser.hpp"
#include <string>


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




void Parser::find_siblings( Tree_Node *root_node, vector<Token> token_list ){

    // while token_list is not EMPTY
    while( !token_list.empty() )
    {
        Tree_Node *node;

        // pop first_token off of token_list and switch on its type
        Token first_token = token_list.at( 0 );
        token_list.erase( token_list.begin() );
        switch( first_token.type )
        {

            case EOF:
                token_list.clear();
                break;

            case COMMA:
            case RBRACKET:
            case RBRACE:
            case SEMI:
            {
                break;
            }

            case INT:
            {
                node->nodeType = VARIABLE;
                node->typeSpecifier = INT;
            }

            case VOID:
            {
                node->typeSpecifier = first_token.type;
                if( !token_list.empty() )
                {
                    // pop second_token off of token_list and switch on its type
                    Token second_token = token_list.at( 0 );
                    token_list.erase( token_list.begin() );
                    switch( second_token.type )
                    {

                        case ID:
                        {
                            node->sValue = second_token.value;
                            if( !token_list.empty() )
                            {
                                // pop third_token off of token_list and switch on its type
                                Token third_token = token_list.at( 0 );
                                token_list.erase( token_list.begin() );
                                switch( third_token.type )
                                {

                                    case LBRACKET:
                                    {
                                        // pop fourth_token off of token_list and switch on its type
                                        node->nodeType = ARRAY;
                                        Token fourth_token = token_list.at( 0 );
                                        token_list.erase( token_list.begin() );
                                        switch( fourth_token.type )
                                        {

                                            case NUMBER:
                                            {
                                                node->nValue = std::stoi( fourth_token.value );
                                                break;
                                            }

                                            case RBRACKET:
                                            {
                                                break;
                                            }

                                            default:
                                            {
                                              cerr << "ERROR: Unhandled fourth_token type: " << fourth_token.type << endl;
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
                                        // LPAREN means we are declaring a function
                                        node->nodeType = FUNCTION;
                                        node->C1 = new Tree_Node();
                                        node->C1->nodeType = PARAMETER_LIST;
                                        // Get iterator pointing to first instance of RPAREN
                                        vector<Token>::iterator right_paren = std::find( token_list.begin(), token_list.end(), RPAREN );
                                        if ( right_paren == token_list.end() )
                                        {
                                            node->C1->typeSpecifier = VOID;
                                        }
                                        else
                                        {
                                            node->C1->typeSpecifier = INT;
                                            vector<Token> passed_list;
                                            std::move( token_list.begin(), right_paren, passed_list.begin() );
                                            build_subtree( node->C1, passed_list );
                                        }
                                        node->C2 = new Tree_Node();
                                        node->C2->nodeType = PARAMETER_LIST;
                                        // Get iterator pointing to first instance of LBRACE
                                        vector<Token>::iterator open_brace = std::find( token_list.begin(), token_list.end(), LBRACE );
                                        
                                        int num_of_open_braces = 1;
                                        int num_of_closed_braces = 0;
                                        vector<Token>::iterator close_brace;
                                        vector<Token>::iterator index = open_brace;
                                        do
                                        {
                                            index += 1;
                                            int position = std::distance( token_list.begin(), index );
                                            if( position == token_list.size() )
                                            {
                                                cerr << "ERROR: Parenthesis mismatch" << endl;
                                                exit(-1);
                                            }
                                            Token token = token_list.at( position );
                                            switch( token.type )
                                            {
                                                case LBRACE:
                                                {
                                                    num_of_open_braces += 1;
                                                    break;
                                                }

                                                case RBRACE:
                                                {
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
                                        
                                        vector<Token> passed_list;
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
                                        root_node->sibling = node;
                                        root_node = node;
                                        break;
                                    }

                                    default:
                                    {
                                        cerr << "ERROR: Unhandled third_token type: " << third_token.type << endl;
                                        exit(-1);
                                    }
                                }
                            }
                            else
                            {
                                root_node->sibling = node;
                                root_node = node;
                            }
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token.type << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }

            case ID:
            {
                break;
            }

            default:
            {
                cerr << "ERROR: Unhandled first_token type: " << first_token.type << endl;
                exit(-1);
            }
        }
    }
}




void Parser::find_arguments(Tree_Node *root_node, vector<Token> token_list ){

    while( !token_list.empty() )
    {
        Tree_Node *node;
        Token first_token = token_list.at( 0 );
        token_list.erase( token_list.begin() );
        switch( first_token.type )
        {

            case NUMBER:
            {
                if( token_list.empty() )
                {
                    node->nodeType = NUMBER;
                    node->typeSpecifier = INT;
                    node->nValue = std::stoi( first_token.value );
                }
                else
                {
                    Token second_token = token_list.at( 0 );
                    token_list.erase( token_list.begin() );
                    switch( second_token.type )
                    {

                        case COMMA:
                        {
                            node->nodeType = NUMBER;
                            node->typeSpecifier = INT;
                            node->nValue = std::stoi( first_token.value );
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token.type << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }

            case ID:
            {
                if( token_list.empty() )
                {
                    node->nodeType = VARIABLE;
                    node->sValue = first_token.value;
                }
                else
                {
                    Token second_token = token_list.at( 0 );
                    token_list.erase( token_list.begin() );
                    switch( second_token.type )
                    {
                        case COMMA:
                        {
                            node->nodeType = VARIABLE;
                            node->sValue = first_token.value;
                            break;
                        }

                        default:
                        {
                            cerr << "ERROR: Unhandled second_token type: " << second_token.type << endl;
                            exit(-1);
                        }
                    }
                }
                break;
            }
            default:
            {
                cerr << "ERROR: Unhandled first_token type: " << first_token.type << endl;
                exit(-1);
            }
        }
        root_node->sibling = node;
        root_node = node;
    }
}



void Parser::find_expression(Token first_token, Tree_Node *root_node, vector<Token> token_list ){
    Tree_Node *node = new Tree_Node();
    while( !token_list.empty() )
    {
        if( first_token == NULL )
        {
            Token first_token = token_list.at( 0 );
            token_list.erase( token_list.begin() );
        }

        
        node->nodeType = EXPRESSION;
        node->C1 = new Tree_Node();
        node->C1->sValue = first_token.value;
        switch( first_token.type )
        {

            case NUMBER:
            {
                node->C1->nodeType = NUMBER;
                node->C1->typeSpecifier = INT;
                node->C1->nValue = std::stoi( first_token.value );
                break;
            }

            case ID:
                node->C1->nodeType = VARIABLE;
                if( !token_list.empty() )
                {
                    Token second_token = token_list.at( 0 );
                    token_list.erase( token_list.begin() );
                    switch( second_token.type )
                    {

                        case LBRACKET:
                        {
                            node->C1->nodeType = ARRAY;
                            Token third_token = token_list.at( 0 );
                            token_list.erase( token_list.begin() );
                            switch( third_token.type )
                            {

                                case INT:
                                {
                                    node->C1->nValue = std::stoi( third_token.value );
                                    token_list.erase( token_list.begin() );
                                    break;
                                }

                                case ID:
                                {
                                    vector<Token>::iterator index = std::find( token_list.begin(), token_list.end(), SEMI );
                                    vector<Token> passed_list;
                                    std::move( (token_list.begin() + 1), index, passed_list.begin() );
                                    find_expression( third_token, node->C1, passed_list);
                                    node->C1 = node->C1->sibling;
                                    break;
                                }

                                default:
                                {
                                    cerr << "ERROR: Unhandled third_token type: " << third_token.type << endl;
                                    exit(-1);
                                }
                            }
                            break;
                        }

                        case MINUS:
                        {
                            node->nodeType = MINUS;
                            node->C2 = new Tree_Node();
                            vector<Token>::iterator index = std::find( token_list.begin(), token_list.end(), MINUS );
                            find_expression(NULL, node->C2, token_list);
                            token_list.erase( token_list.begin(), index );
                            node->C2 = node->C2->sibling;
                            break;
                        }

                        case LS:
                        {
                            node->nodeType = LS;
                            node->C2 = new Tree_Node();
                            vector<Token>::iterator index = std::find( token_list.begin(), token_list.end(), SEMI );
                            find_expression(NULL, node->C2, token_list);
                            token_list.erase( token_list.begin(), index );
                            node->C2 = node->C2->sibling;
                            break;
                        }

                        case ASSIGN:
                        {
                            Token third_token = token_list.at( 0 );
                            token_list.erase( token_list.begin() );
                            switch( third_token.type )
                            {

                                case NUMBER:
                                {
                                    node->nodeType = ASSIGN;
                                    node->C2 = new Tree_Node();
                                    node->C2->nodeType = NUMBER;
                                    node->C2->typeSpecifier = INT;
                                    node->C2->nValue = stoi( third_token.value );
                                    break;
                                }

                                case ID:
                                {
                                    node->C2 = new Tree_Node();
                                    if ( token_list.empty() )
                                    {
                                        node->C2->nodeType = VARIABLE;
                                        node->C2->sValue = third_token.value;
                                    }
                                    else
                                    {
                                        Token fourth_token = token_list.at( 0 );
                                        token_list.erase( token_list.begin() );
                                        switch( fourth_token.type )
                                        {

                                            case LPAREN:
                                            {
                                                node->C2->nodeType = CALL;
                                                node->C2->sValue = third_token.value;
                                                node->C2->typeSpecifier = INT;
                                                node->C2->C1 = new Tree_Node();
                                                node->C2->C1->nodeType = ARGUMENTS;
                                                vector<Token>::iterator right_paren = std::find( token_list.begin(), token_list.end(), RPAREN );
                                                vector<Token> passed_list;
                                                std::move( token_list.begin(), right_paren, passed_list.begin() );
                                                find_arguments(node->C2->C1, passed_list);
                                                break;
                                            }

                                            case SEMI:
                                            {
                                                node->C2->nodeType = VARIABLE;
                                                node->C2->sValue = third_token.value;
                                                break;
                                            }

                                            case LBRACKET:
                                            {
                                                node->C2->nodeType = ARRAY;
                                                node->C2->sValue = third_token.value;
                                                node->C2->C1 = new Tree_Node();
                                                vector<Token>::iterator right_bracket = std::find( token_list.begin(), token_list.end(), RBRACKET );
                                                vector<Token> passed_list;
                                                std::move( token_list.begin(), right_bracket, passed_list.begin() );
                                                find_expression( NULL, node->C2->C1, passed_list );
                                                node->C2->C1 = node->C2->C1->sibling;
                                                break;
                                            }

                                            case PLUS:
                                            {
                                                node->C2->nodeType = PLUS;
                                                node->C2->C1 = node;
                                                Tree_Node *temp_node = node->C2;
                                                node->C2 = NULL;
                                                node->C2 = new Tree_Node();
                                                vector<Token>::iterator index = token_list.end();
                                                vector<Token> passed_list;
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
                                               cerr << "ERROR: Unhandled fourth_token type: " << fourth_token.type << endl;
                                               exit(-1);
                                            }
                                        }
                                    }
                                    break;
                                }

                                default:
                                {
                                   cerr << "ERROR: Unhandled third_token type: " << third_token.type << endl;
                                   exit(-1);
                                }
                            }
                            break;
                        }

                        default:
                        {
                           cerr << "ERROR: Unhandled second_token type: " << second_token.type << endl;
                           exit(-1);
                        }
                    }
                }
                // break;
                default:
                {
                    cerr << "ERROR: Unhandled first_token type: " << first_token.type << endl;
                    exit(-1);
                }
            }
            
            
        }

        while( !token_list.empty() && ( token_list.at(0).type == SEMI ) )
        {
            token_list.erase( token_list.begin() );
        }

        root_node->sibling = node;
        root_node = node;
        first_token = NULL;
    //}
}



void Parser::find_statement_list_siblings(Tree_Node *root_node, vector<Token> token_list ){

    // while token_list is not EMPTY
        // create new node
        // pop first_token off of token_list
        // switch on first_token.type
            // WRITE ->
                // set node.nodeType to WRITE
                // set close_paren to index of RPAREN in token_list
                // create node.C1 child node
                // set node.C1.nodeType to EXPRESSION
                // call find_expression(null, node.C1, token_list(from 1 to close_paren))
                // set token_list to token_list(from close_paren+1 to end of token_list)
                // break;
            // READ ->
                // set node.nodeType to READ
                // pop second_token off of token_list
                // switch on second_token.type
                    // ID ->
                        // get third_token from beginning of token_list (not a pop, leave value)
                        // create new node.C1 child node
                        // switch on third_token.type
                            // ID ->
                                // set node.C1.nodeType to VARIABLE
                                // set node.C1.nValue to int(second_token.value)
                                // break;
                            // LBRACKET
                                // set node.C1.nodeType to ARRAY
                                // set node.C1.sValue to second_token.value
                                // set index to RBRACKET in token_list
                                // set token_list to token_list(from index to end of token_list)
                                // break;
                            // default -> error out on unhandled third_token.type; exit
                        // break
                    // default -> error out on unhandled second_token.type; exit
                // break;
            // INT ->
                // create new_token_list
                // add first_token to beginning of new_token_list
                // for i < token_list.size
                    // append token_list[i] to new_token_list
                // set node.nodeType to compound
                    // set close_brace to index of RBRACE in new_token_list
                    // if close_brace is not valid
                        // set close_brace to end of new_token_list
                    // call build_subtree(node, new_token_list(from 0 to close_brace))
                    // set new_token_list to new_token_list(from close_brace to end of new_token_list)
                // set token_list to new_token_list
                // break;
            //RETURN ->
                // set node.nodeType to RETURN
                // create node.C1 child node
                // set indext to index of SEMI in token_list
                // call find_expression(null, node.C1, token_list(from 0 to index))
                // set token_list to token_list(from index+1 to end of token_list)
                // set node.C1 to node.C1.sibling
                // break
            // IF ->
                // set node.nodeType to IF
                // create node.C1 child node
                    // set close_paren to index of RPAREN in token_list
                    // call find_expression(null, node.C1, token_list(from 1 to indext))
                    // set token_list to token_list(from index+1 to end of token_list)
                // set node.C1 to node.C1.sibling
                // create node.C2 child node
                // set node.C2.nodeType to compound
                    // set close_brace to index of RBRACE in token_list
                    // if close_brace is invalid
                        // set close_brace to end of token_list
                    // call build_subtree(node.C2, token_list(from 1 to close_brace))
                // create node.C3 child node
                // set node.C3.nodeType to compound
                    // set close_brace to index of RBRACE in token_list
                    // call build_subtree(node.C3, token_list(from 1 to close_brace))
                    // set token_list to token_list(from close_brace+1 to end of token_list)
                // break;
            // ID ->
                // pop second_token off token_list
                // switch on second_token.type
                    // LBRACKET ->
                        // set node.nodeType to EXPRESSION
                        // set index to index of SEMI in token_list
                        // call find_expression(first_token, node, token_list(from 0 to index))
                        // set token_list to token_list(from index+1 to end of token_list)
                        // break
                    // ASSIGN ->
                        // set node.nodeType to ASSIGN
                        // create node.C1 child node
                        // set node.C1.nodeType to VARIABLE
                        // set node.C1.sValue to first_token.value
                        // create node.C2 child node
                        // set index to index of SEMI from token_list
                        // call find_expression(first_token, node.C2, token_list(from 0 to index))
                        // set token_list to token_list(from index + 1 to end of token_list)
                        // set node.C2 to node.C2.sibling
                        // break
                    // LPAREN
                        // pop the first element off token_list
                        // set node.nodeType to call
                        // set node.sValue to first_token.value
                        // set node.typeSpecifier to INT
                        // create node.C1 child node
                        // set node.C1.nodeType to ARGUMENTS
                        // set close_paren to index of RPAREN in token_list
                        // if close_paren is not valid
                            //set close_paren to end of token_list
                        // call find_arguments(node.C1, token_list(from 0 to close_paren))
                        // set token_list to token_list(from index + 1 to end of token_list)
                        // break
                    // default -> error out on unhandled second_token.type; exit
                // break
            // CALL ->
                // set node.nodeType to call
                // break
            // WHILE ->
                // set node.nodeType to WHILE
                // create node.C1 child node
                // set node.C1.nodeType to EXPRESSION
                    // set close_paren to index of RPAREN in token_list
                    // call find_expression(null, node.C1, token_list(from 1 to close_paren))
                    // set token_list to token_list(from close_paren+1 to end of token_list)
                // set node.C1 to node.C1.sibling
                // create node.C2 child node
                // set node.C2.nodeType to STATEMENT_LIST
                    // set open_brace to index of LBRACE in token_list
                    // declare close_brace
                    // find matching braces
                        // set num_of_open_braces to 1
                        // set num_of_closed_braces to 0
                        // index to open_brace
                        // do
                            // increment index
                            // get token from token_list at index
                            // switch on token.type
                                // LBRACE ->
                                    // increment num_of_open_braces
                                    // break
                                // RBRACE ->
                                    // increment num_of_closed_braces
                                    // break
                                // default ->
                                    // break
                        // while num_of_open_braces != num_of_closed_braces
                        // set close_brace to index
                        // increment open_brace
                    // call build_subtree(node.C2, token_list(from open_brace to close_brace))
                    // set token_list to token_list(from close_brace+1 to end of token_list)
                // break
            // default -> error out on unhandled first_token.type; exit
        // while token_list is not EMPTY and the next token is SEMI
            // pop the SEMI off the token_list
        // set root_node.sibling to node
        // set root_node to node
}




void Parser::build_subtree(Tree_Node *root_node, vector<Token> token_list ){

    // switch on root_node.type
        // PROGRAM -->
            // call find_siblings(root_node, token_list)
            // break
        // PARAMETER_LIST
            // create new node
            // set node to root_node
            // switch on node.typeSpecifier
                // VOID -> break;
                // INT -> call find_siblings(root_node, token_list); break
                // default -> error out on unhandled node.typeSpecifier; exit
            // break
        // COMPOUND ->
            // create root_node.C1 child
            // set root_node.C1.nodeType to DECLARATION
                // set keep_going to TRUE
                // set index to 0
                // do
                    // get token at index of token_list
                    // switch on token.type
                        // INT -> index += 3; break
                        // default -> set keep_going to FALSE; break
                // while keep_going
                // if index > 0
                    // call find_siblings(root_node.C1, token_list(from - to index))
                    // set token_list to token_list(from index+1 to end of token_list)
            // create root_node.C2 child nodeType
            // set root_node.C2.nodeType to STATEMENT_LIST
            // call build_subtree(root_node.C2, token_list)
            // break
        // STATEMENT_LIST ->
            // call find_statement_list_siblings(root_node, token_list)
            // break
        // default -> error out on unhandled root_node.nodeType; exit
}
