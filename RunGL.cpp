#define var GLfloat
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))//to_use-> COUNT_OF( floorTile_2m_INDICES)
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//=======================================================================================================================
    
    
    
#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT
        #define   glGenFramebuffers      glGenFramebuffersEXT
        #define   glBindFramebuffer      glBindFramebufferEXT
        #define   glDeleteFramebuffers   glDeleteFramebuffersEXT        
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT
         
         
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
       // #include <iostream.h>
        #include <fstream.h>
        #include <vector>
        //using namespace std; //___used for string object

        //-----------------------------------------------------------------------------
        #include <GL/gl.h>
        #include <GL/glu.h>
        #include "headerFiles/glext.h"
        #include "headerFiles/glext_Init_A.cpp"
        //=====================================
        void InitGL(void);
        void RenderGL(void);
        void KillALData(void);
        void ProcessKeyboard(void);
        void shutDownGL(void); 
        bool CreateDummyGLWindow();       
        //=========================
        int  screenWidth;
        int  screenHeight; 
        int  viewWidth;
        int  viewHeight;        
        //----------------------------------------------------------------------
        GLfloat  Pass_MIDDLE_Mouse[2];
        GLfloat  Pass_MIDDLE_CONTROL_Mouse;
        GLfloat  Pass_MIDDLE_SHIFT_Mouse[2];        
        //-------------------------------
        bool keys[256], keypressed[256];
        bool mkeyIsReset = true;
        
        //#include "cpp/winInit.cpp"
        #include "cpp/WGL_ARB_multisample.h"
        //-------------------------------

        #include "headerFiles/VSync.h"
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------


#endif

//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================

bool sound_API_selector = 0;//_0_is_openAL_/_1_is_fMod

//=========================================================
GLfloat frequency[512];
GLfloat audioRotation[] = {1.0, 0.0, 1.0, 0.0};
GLfloat directionSoundTravels = 1.0;
GLuint  selectFrequency = 4;
//----------------------------------------------
#ifdef __APPLE__
        //--------------
        int  viewWidth;
        int  viewHeight;
        //----------------------------------------------
        #include "AUDIO/openAL_iOS/openAL_iOS_GLOBALS.cpp"
        //-----------------------------------------------
//        #import "fmod.hpp"
//        #import "fmod_errors.h"
        GLfloat frequency_fMod_iOS[64];

//        #include "AUDIO/fMod_iOS/fMod_iOS_GLOBALS.cpp" //_____found_in_EAGLView

        

#endif
//=========================================================
#ifdef WIN32
        
       #include "AUDIO/openAL_WIN/openAL_WIN_GLOBALS.cpp"
        //-----------------------------------------------
       #include "AUDIO/fMod_WIN/fMod_WIN_GLOBALS.cpp"
        int        playing  = 0;
        int       *channel  = 0;
        bool       playOnce = true;
        
#endif
//=========================================================




//=======================================================================================================================

GLfloat adjust_w = 1.0;

#include <math.h>
  
//=======================================================================================================================

#include "MATRIX_MATH.cpp"

//=======================================================================================================================


//--------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
        extern GLuint msaaFramebuffer;
        extern GLuint viewRenderbuffer;

        bool iOS_MSAA_IS_ON = true;
        
        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef __APPLE__
               GLuint  viewFramebuffer;
        #endif
          
        //-------------------------------------------------------------------------------


        GLuint m_uiShadowMapTexture;
        GLuint m_uiFrameBufferObject;



//=======================================================================================================================
//=======================================================================================================================


void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //---------------
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        ////glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
        //---------------
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //----------------
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	  
        //----------------        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0);
        //----------------
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif
}

//===============================================================================================================================

var     view[16];
var     view_Rotate[16];
var     modelWorld[16];
var     modelView[16];
var     projection[16];

var     modelRotation[16];

var     lightMatrix[16];

var     light_ModelWorld[16];
var     light_View[16];
var     light_ModelView[16];
var     light_Projection[16];
var     ShadowLight_TextureMatrix[16];
var     invertView[16];

var     biasMatrix[] = {0.5, 0.0, 0.0, 0.0, 
                        0.0, 0.5, 0.0, 0.0, 
                        0.0, 0.0, 0.5, 0.0, 
                        0.5, 0.5, 0.5, 1.0};






//============================================================================================================================

var     moveShadowPivot_Z = 0.0;

//============================================================================================================================

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================



//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

 
#include "GLOBALS.cpp"
  
//============================================================================================================================

//============================================================================================================================

void setupTransforms_MainColor(void)
{
        
        LoadIdentity(view);
        Translate(view,             eyeposition[0], 
                                    eyeposition[1], 
                                    eyeposition[2]);


        //===========================================
        LoadIdentity(invertView);
        InvertMatrix(invertView, view);
        //=============================
        
        LoadIdentity(view_Rotate);
        //--------------------   
        Rotate(view_Rotate, 1.0, 0.0, 0.0, rotateModelWithMiddleMouse[0]);
        Rotate(view_Rotate, 0.0, 1.0, 0.0, rotateModelWithMiddleMouse[1]);        
}

//============================================================================================================================


void setupTransforms_Shadows(void)
{
        LoadIdentity(light_View);
        //-------------------------------------------------
        Translate(light_View,       eyeposition_SHADOW[0] + eyeposition[0] * scaleViewMovement[0],
                                    eyeposition_SHADOW[1],
                                    eyeposition_SHADOW[2]);
        


}

//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================

var shaderNumber = 0;

void SelectShader(var shaderNumber)
{
        
        if(shaderNumber == 47)
        {
                #include "_SHADERS/SHADOWS/shadow_32bit_Stride_SHADER_RENDER.cpp"
        }  
        
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 50)
        {
                #include "_SHADERS/leaves/A/leaves_A_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------



}

//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================



void InitGL( void )//__BEGIN_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
{
        //==========================================================================
        #ifdef WIN32
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp"
            alutInit(NULL, 0);
            //-------------------------------------
            SetVSyncState(true);
            //-----------------------------------------------------------------------------
                        rotateModelWithMiddleMouse[0] = Pass_MIDDLE_Mouse[0];
                        rotateModelWithMiddleMouse[1] = Pass_MIDDLE_Mouse[1];
                        //-----------------------------------------------------------------
                        zoomModelWithMiddleMouse      = Pass_MIDDLE_CONTROL_Mouse;
                        //-----------------------------------------------------------------     
                        moveModelWithMiddleMouse[0]   = Pass_MIDDLE_SHIFT_Mouse[0];
                        moveModelWithMiddleMouse[1]   = Pass_MIDDLE_SHIFT_Mouse[1];
                        //-----------------------------------------------------------------       
       
        //=================
        #endif
                   
//################################################################################################################################
/*
        #ifdef __APPLE__
        
                if(sound_API_selector == 0)
                {
                        #include "AUDIO/openAL_iOS/openAL_iOS_Init.cpp"
                }        
                if(sound_API_selector == 1)
                {        
                        //#include "AUDIO/fMod_iOS/fMod_iOS_Init.cpp" //_____found_in_EAGLView
                }
        
        #endif
        //=========================================================
        #ifdef WIN32
                
                if(sound_API_selector == 0)
                {
                        #include "AUDIO/openAL_WIN/openAL_WIN_Init.cpp"
                }
                
                if(sound_API_selector == 1)
                {    
                        #include "AUDIO/fMod_WIN/fMod_WIN_Init.cpp"
                }
        
        #endif
*/
//=======================================================================================================================
//=======================================================================================================================
       
#ifdef WIN32        
        //===================================================================================================
        glGenTextures(1, &m_uiShadowMapTexture);
	    glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);
        //-------------------------------------------------
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,  NULL);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2048 * resize_SHADOW_FBO, 2048 * resize_SHADOW_FBO, 0, GL_DEPTH_COMPONENT,  GL_UNSIGNED_INT,  NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //------------------------------------------------------------------
	    glGenFramebuffers(1, &m_uiFrameBufferObject);
	    glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);
        //---------------------
        glDrawBuffer(GL_NONE);//_ON_SOME_MACHINES_THIS_IS_REQUIRED / ON_SOME_IT_FAILS
        glReadBuffer(GL_NONE);//_SAME_AS_ABOVE
	    //---------------------
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uiShadowMapTexture, 0);     
        glBindFramebuffer(GL_FRAMEBUFFER, 0);        
        //====================================================================================================
#endif
        
//==================================================================================================================================================        
        //NSLog(@"viewWidth: %f", (GLfloat)viewWidth);   
        //NSLog(@"viewHeight: %f", (GLfloat)viewHeight);   

#ifdef __APPLE__
        //====================================================================================================
        glGenTextures(1, &m_uiShadowMapTexture);
	    glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);
        //-------------------------------------------------
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 2000, 1000, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //------------------------------------------------------------------
	    glGenFramebuffers(1, &m_uiFrameBufferObject);
	    glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);
        //---------------------
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_uiShadowMapTexture, 0);     
        glBindFramebuffer(GL_FRAMEBUFFER, 0);        
        //====================================================================================================
 #endif
//=======================================================================================================================
//=======================================================================================================================
/*
GLuint framebuffer;
glGenFramebuffers(1, &framebuffer);
glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

GLuint depthRenderbuffer;
glGenRenderbuffers(1, &depthRenderbuffer);
glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei)viewWidth, (GLsizei)viewHeight);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
*/





    glGenFramebuffers( 1, &(frame_buffer ) );
    glGenTextures(1, &(colour_texture) );
    glBindTexture(GL_TEXTURE_2D, colour_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &(depth_texture) );
    glBindTexture(GL_TEXTURE_2D, depth_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (GLsizei)viewWidth, (GLsizei)viewHeight,  0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);        

    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_TEXTURE_2D, depth_texture, 0);
                    
                


//=======================
#include "INITIALIZE.cpp"
//=======================



GLfloat adjustToResolution = (GLfloat)viewWidth/1920;


//=====================================================================================================
//-----------------------------------------------------------------------------------------------------
//_____________________________________________________________________________________________________
#ifdef WIN32
        
        display_00_SCALE[0] = 1.0/(GLfloat)viewWidth * (GLfloat)viewWidth * adjustToResolution*4.52/10;   
        display_00_SCALE[1] = display_00_SCALE[0]; 
        
        //------------------------------------------------------------------------------------------------
        scaleScreenAlignedQuadRatio   = (GLfloat)viewWidth / (GLfloat)viewHeight;
        //-----------------------------------------------------------------------
        inverseScreenRatio            = 1.0 / (GLfloat)viewWidth * (GLfloat)viewHeight; 
        display_00_MOVE[0]           += inverseScreenRatio * display_00_SCALE[0] * 0.5; 
        display_00_MOVE[1]           -=  display_00_SCALE[1] * 0.5;
        //------------------------------------------------------------------------------------------------
        GLfloat skipTouchIncrement = display_00_SCALE[1] / scaleScreenAlignedQuadRatio;
        display_00_MOVE[0] += skipTouchIncrement;

#endif       
   
#ifdef __APPLE__
        
        display_00_SCALE[0] = 1.0/(GLfloat)viewWidth * (GLfloat)viewWidth * adjustToResolution*4.52/10*4.0;   
        display_00_SCALE[1] = display_00_SCALE[0]; 
        
        //-----------------------------------------------------------------------
        scaleScreenAlignedQuadRatio   =  (GLfloat)viewWidth / (GLfloat)viewHeight;
        //-----------------------------------------------------------------------
        inverseScreenRatio            = (1.0 / (GLfloat)viewHeight) * viewWidth; 
        display_00_MOVE[1]           -=  inverseScreenRatio * display_00_SCALE[0] * 0.5; 
        display_00_MOVE[0]           -=  display_00_SCALE[1] * 0.5 ;        
        //------------------------------------------------------------------------------------------------
        GLfloat skipTouchIncrement = display_00_SCALE[1] * scaleScreenAlignedQuadRatio;
        display_00_MOVE[1] -= skipTouchIncrement;


#endif        
//_____________________________________________________________________________________________________   
//-----------------------------------------------------------------------------------------------------   
//=====================================================================================================   


       
       
       
//==============================================================================
    #ifdef WIN32   
        atexit(KillALData);//_tell_openAL_to_run_KillALData_function_at_shutdown 
#endif    
        
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
        
//====================================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================



void RenderGL(void)
{


//=======================================================================================================================

        
                        //=================================================================
                        #ifdef __APPLE__   
                        //--------------         
                                //eyeposition[0] -= PassTouchMovement[0];
                                //eyeposition[1] -= PassTouchMovement[1];
                                //eyeposition[2] -= PassTouchMovement[2];                   
                        
                                //PassTouchMovement[0] = 0.0;
                                //PassTouchMovement[1] = 0.0;
                                //PassTouchMovement[2] = 0.0;
                        
                        //--------------                        
                        #endif 
                        //=================================================================
                                      
                        //=================================================================        
                        #ifdef WIN32  
                        //------------
                                rotateModelWithMiddleMouse[0] = Pass_MIDDLE_Mouse[0];
                                rotateModelWithMiddleMouse[1] = Pass_MIDDLE_Mouse[1];
                                //-------------------------------------------------------
                                zoomModelWithMiddleMouse = Pass_MIDDLE_CONTROL_Mouse;
                                //-------------------------------------------------------
                                moveModelWithMiddleMouse[0] = Pass_MIDDLE_SHIFT_Mouse[0];
                                moveModelWithMiddleMouse[1] = Pass_MIDDLE_SHIFT_Mouse[1];
                        //------------ 
                        #endif            
                        //=================================================================  
       
//============================================================================================================================       
//turnTable += 0.1;

        
        
        



//====================================================================================================================================
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
//====================================================================================================================================
        #include "runDepth_FBO.cpp"
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	    //glDepthMask(0);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
        //glDepthFunc(GL_EQUAL);    
//====================================================================================================================================
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE______________FRAMEBUFFER_SHADOWS_BEGINS_HERE___________________________________
//====================================================================================================================================



//====================================================================================================================================
//====================================================================================================================================

#ifdef WIN32    
        // glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mainLightPass_fboId);
        // glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mainLightPass_depth);
#endif         
      

    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
        //==============================----------------------------------------
        #include "drawMainColor_FBO.cpp"
        //==============================----------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  


   
        
  

#ifdef __APPLE__

        if(iOS_MSAA_IS_ON)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);     
        }else 
        {
            glBindFramebuffer(GL_FRAMEBUFFER, viewRenderbuffer);  
        }
        
#endif
//===============================================================================================================  
//=====================================

//=====================================   


//=====================================================================================================================
//=====================================================================================================================

        glActiveTexture (GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depth_texture);
        glActiveTexture (GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colour_texture);//facing_UP_TEXTUREMAP
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Render.cpp"

//=====================================================================================================================
//======================================================================================================================

        

marc_ROTATE[3] += 0.1;




        
}//_END_RenderGL()//#####################################################################################################


//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================

#ifdef WIN32
void ProcessKeyboard(void)
{
/*    if (keys['L'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[0]         +=  1.011;
    }
    if (keys['J'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[0]         -=  1.011;
    }    
    if (keys['I'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[1]         += 1.011;
    } 
    if (keys['K'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[1]         -=  1.011;
    }
    if (keys['O'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[2]         +=  1.011;
    }
    if (keys['U'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])  
    {
             eyeposition_SHADOW[2]         -=  1.011;
    }
*/   //--------------------------------------------------------------------------


    //=======================================================================================
    if (keys[VK_NUMPAD6])
    {
             marc_POSITION[0]         +=  0.01;
             //eyeposition[0]             -=  0.01;
             //lookAt[0]                  -=  0.01;
    }
    if (keys[VK_NUMPAD4])
    {
             marc_POSITION[0]         -=  0.01;
             //eyeposition[0]             +=  0.01;
             //lookAt[0]                  +=  0.01;
    }
    if (keys[VK_NUMPAD8])
    {
             marc_POSITION[1]         +=  0.01;
             //eyeposition[1]             -=  0.01;
             //lookAt[1]                  -=  0.01; 
    }
    if (keys[VK_NUMPAD2])
    {
             marc_POSITION[1]         -=  0.01;
             //eyeposition[1]             +=  0.01;
             //lookAt[1]                  +=  0.01;  
    }
    if (keys[VK_NUMPAD7])
    {
             marc_POSITION[2]         +=  0.01;
             //eyeposition[2]             -=  0.01;
             //lookAt[2]                  -=  0.01;     
    }
    if (keys[VK_NUMPAD9])
    {
             marc_POSITION[2]         -=  0.01;
             //eyeposition[2]             +=  0.01;
             //lookAt[2]                  +=  0.01;     
    }
    
    //=================================================================================================================      
    if (keys[VK_LEFT])
    {
             moveSet[0]         -=  0.01;
   }
    if (keys[VK_RIGHT])
    {
             moveSet[0]         +=  0.01;
   }
    if (keys[VK_UP])
    {
             moveSet[1]         -=  0.01;
   }
    if (keys[VK_DOWN])
    {
             moveSet[1]         +=  0.01;
    }       
    //=================================================================================================================    
    //--------------------------------------------------------------------------    
    //======================================__LIGHTING__======================
    if (keys['L'] && keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             room_10_POSITION[0]         +=  0.01;
    }
    if (keys['J'] && keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             room_10_POSITION[0]         -=  0.01;
    }    
    if (keys['I'] && keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             room_10_POSITION[1]         += 0.01;
    } 
    if (keys['K'] && keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             room_10_POSITION[1]         -=  0.01;
    }
    if (keys['O'] && keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             room_10_POSITION[2]         +=  0.01;
    }
    if (keys['U'] && keys[VK_SHIFT] && !keys[VK_CONTROL])  
    {
             room_10_POSITION[2]         -=  0.01;
    }    
  
    //=================================================================================================================    
    //--------------------------------------------------------------------------    
    //======================================__LIGHTING__======================
    if (keys['M'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
            scaleViewMovement[0]               +=  0.001;
    }
    if (keys['N'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
            scaleViewMovement[0]               -=  0.001;
    }
    if (keys['X'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
            shadow_BIAS               +=  0.000001;
    }
    if (keys['Z'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
            shadow_BIAS               -=  0.000001;
    }      
    //======================================__LIGHTING__======================    
    //--------------------------------------------------------------------------       
    //=================================================================================================================    


  
    if(keys[VK_F8] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
         ofstream outSettings("settings.cpp");
             
         //------------------------------------------------------------------------------------------------------------------------------
        
         outSettings << "var         marc_POSITION[]    =  {"   
                                  << marc_POSITION[0] << ", "
                                  << marc_POSITION[1] << ", "
                                  << marc_POSITION[2] << ", "
                                  << marc_POSITION[3] << "};\n\n";
         //------------------------------------------------------------------------------------------------------------------------------        
        
         outSettings << "var         eyeposition_SHADOW[]    =  {"   
                                  << eyeposition_SHADOW[0] << ", "
                                  << eyeposition_SHADOW[1] << ", "
                                  << eyeposition_SHADOW[2] << ", "
                                  << eyeposition_SHADOW[3] << "};\n\n";
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         room_10_POSITION[]    =  {"   
                                  << room_10_POSITION[0] << ", "
                                  << room_10_POSITION[1] << ", "
                                  << room_10_POSITION[2] << ", "
                                  << room_10_POSITION[3] << "};\n";            
            
            
        //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var          scaleViewMovement[0]        =  "    
                                  <<  scaleViewMovement[0]        << ";\n\n";   
         //------------------------------------------------------------------------------------------------------------------------------
         
         //------------------------------------------------------------------------------------------------------------------------------
        outSettings << "var          shadow_BIAS         =  "    
                                 <<  shadow_BIAS        << ";\n\n";   
         //------------------------------------------------------------------------------------------------------------------------------
          
        // outSettings << "var         numberOfFloorTile_2m_Instances_BATCH_B        =  "    
        //                          << numberOfFloorTile_2m_Instances_BATCH_B       << ";\n";   
         //------------------------------------------------------------------------------------------------------------------------------
        // outSettings << "var         viewHeight        =  "    
        //                          << viewHeight       << ";\n";   
         //------------------------------------------------------------------------------------------------------------------------------
               
         //------------------------------------------------------------------------------------------------------------------------------
                         

         //---------------------------------------------------------------------------------------------------------------------------         
        // outSettings << "var         ambient_hardShinyBumpPlastic      =  "    
        //                          << ambient_hardShinyBumpPlastic     << ";\n\n"; 
         //------------------------------------------------------------------------------------------------------------------------------
        
        // outSettings << "var         scaleTurnTable         =  "    
        //                          << scaleTurnTable         << ";\n";
         //------------------------------------------------------------------------------------------------------------------------------
        /*
         outSettings << "var         marc_POSITION[]       =  {"   
                                  << marc_POSITION[0]      << ", "
                                  << marc_POSITION[1]      << ", "
                                  << marc_POSITION[2]      << "};\n\n";
        */
         //------------------------------------------------------------------------------------------------------------------------------

         outSettings << "var           eyeposition[]      =  {"   
                                    << eyeposition[0]     << ", "
                                    << eyeposition[1]     << ", "
                                    << eyeposition[2]     << ", 0.0};\n";                

         //------------------------------------------------------------------------------------------------------------------------------

         //------------------------------------------------------------------------------------------------------------------------------
        
        outSettings << "var           rotateModelWithMiddleMouse[]       =  {"   
                                    << rotateModelWithMiddleMouse[0]      << ", "
                                    << rotateModelWithMiddleMouse[1]      << "};\n\n"; 
        
         //------------------------------------------------------------------------------------------------------------------------------
        /*
         outSettings << "var           moveSet[]       =  {"   
                                    << moveSet[0]      << ", "
                                    << moveSet[1]      << ", "
                                    << moveSet[2]      << ", 1.0};\n";                
        */
         //------------------------------------------------------------------------------------------------------------------------------
    
    
   //----------------------------------------------------------------------------------------------------------------
        
    }//_END_F8

//=======================================================================================
//---------------------------------------------------------------------------------------
//_______________________________________________________________________________________
if(keys[VK_F8])
{
    GLsizei screenCaptureWidth  = (GLsizei)viewWidth; 
    GLsizei screenCaptureHeight = (GLsizei)viewHeight;        
                
    GLubyte *pixmap =(GLubyte *)malloc(screenCaptureWidth*screenCaptureHeight*4);
    
    glReadPixels(0,0,screenCaptureWidth,screenCaptureHeight,GL_BGRA,GL_UNSIGNED_BYTE,pixmap);
    
    FIBITMAP *texture = FreeImage_ConvertFromRawBits( pixmap, screenCaptureWidth, screenCaptureHeight, screenCaptureWidth*4, 32, 0xFF0000, 0x00FF00, 0x0000FF, true);    
    FreeImage_Save(FIF_BMP, texture, "AAAAA.bmp", 0);         
        
    free(pixmap);                 
}          
//_______________________________________________________________________________________
//---------------------------------------------------------------------------------------
//=======================================================================================



#include "KEYBOARD/keyboard_RESET.c"
//=======================================================================================
    if (keys['A'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[0]   += 0.01;
          marc_POSITION[0] -= 0.01;          
    }	
//-----------------------------------     
    if (keys['D'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[0]   -= 0.01;
          marc_POSITION[0] += 0.01;             
    }
//=================================== 
    if (keys['S'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[1]   += 0.01;
          marc_POSITION[1] -= 0.01;           
    }
//-----------------------------------	
    if (keys['W'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[1]   -= 0.01;       
          marc_POSITION[1] += 0.01;   
//-----------------------------------  
    }    
    if (keys['Q'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[2]   += 0.01;      
          marc_POSITION[2] -= 0.01;    
    }
//===================================   
    if (keys['E'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
	{
          eyeposition[2]   -= 0.01;
          marc_POSITION[2] += 0.01;       
    }
//===================================  	

//=======================================================================================
//=======================================================================================
    if (keys['L'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[0]         +=  0.0101;
    }
    if (keys['J'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[0]         -=  0.0101;
    }    
    if (keys['I'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[1]         +=  0.0101;
    } 
    if (keys['K'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[1]         -=  0.0101;
    }
    if (keys['O'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             eyeposition_SHADOW[2]         +=  0.0101;
    }
    if (keys['U'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])  
    {
             eyeposition_SHADOW[2]         -=  0.0101;
    }

//=======================================================================================
    

    //=================================================================================================================    
    //--------------------------------------------------------------------------    
    //======================================__SELECT_MODEL======================
    if (keys[VK_OEM_PERIOD] && VK_OEM_PERIOD_KeyIsReset && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             selectedModel += 1;
             VK_OEM_PERIOD_KeyIsReset = false;   
    }
    //=============================================================    
    if (keys[VK_OEM_COMMA] && VK_OEM_COMMA_KeyIsReset && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
             selectedModel -= 1;
             VK_OEM_COMMA_KeyIsReset = false;   
    }
    //======================================__SELECT_MODEL__====================     
    //--------------------------------------------------------------------------
    //=================================================================================================================
    //=================================================================================================================
    //--------------------------------------------------------------------------     
    //======================================__BOX_COUNT__====================        
    if (keys[VK_PRIOR] && VK_PRIOR_KeyIsReset && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
         boxCount +=  1;
         VK_PRIOR_KeyIsReset  = false;
    }         
    if (keys[VK_NEXT]  && VK_NEXT_KeyIsReset  && !keys[VK_SHIFT] && !keys[VK_CONTROL])
    {
         boxCount -=  1;
         VK_NEXT_KeyIsReset   = false;    
    }       
    //======================================__BOX_COUNT__====================         
    //--------------------------------------------------------------------------       
    //=================================================================================================================   
    
    
     
   
}//_END_ProcessKeyboard()
#endif


//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================


void shutDownGL( void )
{

//=======================================================================================================================
//=======================================================================================================================
        
        #include "SHUTDOWN.cpp"
        
                                                               
 
 
 
 
}


//=======================================================================================================================
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//=======================================================================================================================

#ifdef WIN32
void KillALData()
{
	alDeleteBuffers(1, &Buffer_dungeonWAV);
	alDeleteSources(1, &Source_dungeonWAV);
    alutExit();
}
#endif




