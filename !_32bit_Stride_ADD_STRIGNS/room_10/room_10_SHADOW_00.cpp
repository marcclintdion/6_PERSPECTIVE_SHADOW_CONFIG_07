       shaderNumber = 47;                                                                                       
       setupTransforms_Shadows();                                                                             
                                                                                                                
       glBindBuffer(GL_ARRAY_BUFFER, room_10_VBO);                                               
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, room_10_INDICES_VBO);                               
       //------------------------------------------------------------------------------------------------------ 
              //---------------------------------------------------------------------------                     
              Translate(modelViewShadow, room_10_POSITION[0] * scaleMoveShadows[0],         
                                              room_10_POSITION[1] * scaleMoveShadows[1],         
                                              room_10_POSITION[2] * scaleMoveShadows[2]);        
              //---------------------------------------------------------------------------                     
              Rotate(modelViewShadow,    room_10_ROTATE[0],                                 
                                              room_10_ROTATE[1],                                 
                                              room_10_ROTATE[2],                                 
                                              room_10_ROTATE[3]);                                
       //------------------------------------------------------------------------------------------------------ 
       SelectShader(shaderNumber);                                                                              
       //------------------------------------------------------------------------------------------------------ 
           //-------------------------------------------------------------------------------------------------- 
           glDrawElements(GL_TRIANGLES, 5598, GL_UNSIGNED_INT, 0);                                              
