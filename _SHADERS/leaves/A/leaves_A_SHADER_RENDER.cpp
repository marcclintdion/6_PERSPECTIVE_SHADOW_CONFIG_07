
    MultiplyMatrix(modelView, view, modelWorld);
    //----------------------------------------------------------------------------------------------------------    
    LoadIdentity(ShadowLight_TextureMatrix);
    MultiplyMatrix(ShadowLight_TextureMatrix, biasMatrix, light_Projection);    
    MultiplyMatrix(ShadowLight_TextureMatrix, ShadowLight_TextureMatrix, light_View);    //MULTIPLY THESE TO A TEMP MATRIX TO AVOID ROUND OFF ERRORS  
    MultiplyMatrix(ShadowLight_TextureMatrix, ShadowLight_TextureMatrix, invertView);    //MULTIPLY THESE TO A TEMP MATRIX TO AVOID ROUND OFF ERRORS
    //----------------------------------------------------------------------------------------------------------
    LoadIdentity(lightMatrix);
    InvertMatrix(lightMatrix, modelRotation);
    //----------------------------------------------------------------------------------------------------------

 
 glUseProgram(leaves_A_SHADER);
          //------------------------------------------------------------------------------
          glVertexAttribPointer(0,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
          glEnableVertexAttribArray(0);
          glVertexAttribPointer(1,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
          glEnableVertexAttribArray(1);
          glVertexAttribPointer(2,     2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
          glEnableVertexAttribArray(2);
          //------------------------------------------------------------------------------------------------
          glUniform4f(UNIFORM_LIGHT_POSITION_01_leaves_A,              leaves_A_LIGHT_POSITION_01[0],
                                                                       leaves_A_LIGHT_POSITION_01[1],
                                                                       leaves_A_LIGHT_POSITION_01[2],
                                                                       leaves_A_LIGHT_POSITION_01[3]);
         
          glUniform1f(UNIFORM_shininess_leaves_A,                      shadow_BIAS);
          glUniform1f(UNIFORM_ambient_leaves_A,                        ambient_leaves_A);

          //------------------------------------------------------------------------------------------------
          glUniformMatrix4fv(UNIFORM_MODELVIEW_leaves_A,                        1, 0,    modelView);
          glUniformMatrix4fv(UNIFORM_PROJECTION_leaves_A,                       1, 0,    projection);
          glUniformMatrix4fv(UNIFORM_VIEW_leaves_A,                             1, 0,    view);          
          glUniformMatrix4fv(UNIFORM_MODELWORLD_leaves_A,                       1, 0,    modelWorld);          
          glUniformMatrix4fv(UNIFORM_VIEW_ROTATE_leaves_A,                      1, 0,    view_Rotate);            
          
          //---------------
          glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_leaves_A,                     1, 0,    lightMatrix);
          //---------------
          
          glUniformMatrix4fv(UNIFORM_SHADOW_LIGHT_TEXTURE_MATRIX_leaves_A,      1, 0,    ShadowLight_TextureMatrix);
       
          //-------------------------------------------------------------------------------------------------
          glUniform1i(UNIFORM_ShadowTexture_leaves_A,  3);
          glUniform1i(UNIFORM_TEXTURE_DOT3_leaves_A,   1);
          glUniform1i(UNIFORM_TEXTURE_leaves_A,        0);
    //====================================================================================================================

//---------------------------------------------------------------
glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);                                                                                                                          
//---  
