        glEnable(GL_DEPTH_TEST);
        glDepthMask(1);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
        glDepthFunc(GL_LESS);
      
      
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);   

#ifdef WIN32
        //----------------------------------------------------------------
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, (GLsizei)(viewWidth), (GLsizei)(viewHeight));
        //----------------------------------------------------------------

        LoadIdentity(light_Projection);
        PerspectiveMatrix(light_Projection, fieldOfView, (GLfloat)viewWidth  /  (GLfloat)viewHeight,  adjustNearFar_LIGHT[0],  adjustNearFar_LIGHT[1]);

/*
        //----------------------------------------------------------------
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, (2048)-2, (2048)-2);
        //----------------------------------------------------------------

        LoadIdentity(Light_Projection);
        PerspectiveMatrix(Light_Projection, fieldOfView, 2048 / 2048,  adjustNearFar[0],  adjustNearFar[1]);
*/
#endif
   
#ifdef   __APPLE__     
        //----------------------------------------------------------------
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, 2000 - 2, 1000 - 2);
        //----------------------------------------------------------------
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
        LoadIdentity(light_Projection);
        PerspectiveMatrix(light_Projection, fieldOfView, 2000 / 1000,  adjustNearFar_LIGHT[0],  adjustNearFar_LIGHT[1]);
#endif          
      

        //====================================================================================    

shaderNumber = 47;//shadow_32bit_Stride       
setupTransforms_Shadows();         

                                                            
for(float i = 0; i < 6.0*20; i+=6.0)
{    
        //=================================================================================
        room_10_POSITION[0] = i;
        #include "_MODEL_FOLDERS_/room_10/room_10_SHADOW_00.cpp"
        //=================================================================================
      

}
        #include "_MODEL_FOLDERS_/marc/marc_SHADOW_00.cpp"
