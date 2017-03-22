#include "Parser.hpp"


Parser::Parser(){


}

Parser::~Parser(){


}

// Recursively print AST to standard out
Parser::show_tree( TreeNode root_node, String prefix ){

  // print node information: type, specifier, sValue, nValue, rename

  // print child 1 (C1) if not null

  // print child 2 (C2) if not null

  // print child 3 (C3) if not null

}

Parser::find_siblings( TreeNode root_node, token_list){

  // while token_list is not EMPTY
      // create new node
      // pop first_token off of token_list
      // switch on first_token.type
          // EOF -> clear token_list; break
          // COMMA, RBRACKER, RBRACE, SEMI -> break
          // INT -> set node.nodeType to VARIABLE, set node.typeSpecifier to Intrexon
          // VOID ->
              // set node.typeSpecifier to first_token.typeSpecifier
              // pop second_token off of token_list
              // switch on second_token.type
                  // ID ->
                      // set node.sValue to second_token.values
                      // if token_list is not empty
                          // pop third_token off of token_list
                          // switch on third_token.type
                              // LBRACKET ->
                                  // set node.nodeType to Array
                                  // pop fourth_token off of token_list
                                  // switch on fourth_token.type
                                      // NUMBER -> set node.nValue to int(fourth_token.value); break
                                      // RBRACKET -> break;
                                      // default -> error out unhandled fourth_token.type; exit
                                  // set root_node.sibling to node
                                  // set root_node to node
                                  // break;
                              // LPAREN ->
                                  // set node.nodeType to function
                                  // set node.C1 to new node
                                  // set node.C1.nodeType to PARAMETER_LIST
                                  // set end_of_C1 to index of RPAREN in token_list
                                  // if end_of_C1 is not valid
                                      // set node.C1.typeSpecifier to VOID
                                  // else
                                      // set node.C1.typeSpecifier to int
                                      // call build_subtree(node.C1, token_list(from 0 to end_of_C1))
                                      // set token_list to token_list(from (end_of_C1 + 1) to end of token_list)
                                  // set node.C2 to new node
                                  // set node.C2.nodeType to compound
                                  // set start_of_C2 to index of LBRACKET
                                  // set end_of_C2 to null
                                  // find end_of_C2
                                      // set num_of_open_braces to 1
                                      // set num_of_closed_braces to 0
                                      // set index to start_of_C2
                                      // do
                                          // increment index
                                          // get token at token_list[index]
                                          // switch on token.type
                                              // LBRACE -> increment num_of_open_braces; break
                                              // RBRACE -> increment num_of_closed_braces; break
                                              // default -> break;
                                      // while
                                          // num_of_open_braces != num_of_closed_braces
                                      // set end_of_C2 to index
                                      // increment start_of_C2
                                  // call build_subtree(node.C2, token_list(from start_of_C2 to end_of_C2))
                                  // set token_list to token_list(from (end_of_C2 + 1) to end of token_list)
                                  // set root_node.sibling to node
                                  // set root_node to node
                                  // break;
                              // RPAREN, COMMA, SEMI ->
                                  // set root_node.sibling to node
                                  // set root_node to node
                                  // break
                              // default -> error out unhandled third_token.type; exit
                      // else
                          // set root_node.sibling to node
                          // set root_node to node
                      // break;
                  // default -> error out on unhandled second_token.type; exit
          // break;
          // ID -> break;
          // default -> error out on unhandled first_token.type; exit
}




Parser::find_arguments( TreeNode root_node, token_list ){

    // while token_list is not EMPTY
        // create new node
        // pop first_token off of token_list
        // switch on first_token.type
            // NUMBER ->
                // if token_list is EMPTY
                    // set node.nodeType to NUMBER
                    // set node.typeSpecifier to into
                    // set node.nValue to int(first_token.value)
                // else
                    // pop second_token off of token_list
                    // switch on second_token.type
                        // COMMA ->
                            // set node.type to NUMBER
                            // set node.typeSpecifier to int
                            // set node.nValue to int(second_token.value)
                            // break;
                        // default -> error out unhandled second_token.type; exit
                // break;
            // ID ->
                // if token_list is EMPTY
                    // set node.nodeType to VARIABLE
                    // set node.Svalue to first_token.value
                // else
                    // pop second_token off of token_list
                    // switch on second_token.type
                        // COMMA ->
                            //set node.nodeType to VARIABLE
                            // set node.sValue to first_token.value
                            // break;
                        // default -> error out unhandled second_token.type; exit
                //break;
            // default -> error out unhandled first_token.type; exit
        // set root_node.sibling to node
        // set root_node to node
}
