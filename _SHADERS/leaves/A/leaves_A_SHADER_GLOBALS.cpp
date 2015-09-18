                 
var         leaves_A_LIGHT_POSITION_01[]     =  {  -0.168917, 2.0, 20, 1};

var         ambient_leaves_A                 =      1.0; 
var         shininess_leaves_A               =  0;//THIS IS CURRENTLY THE SHADOW BIAS

                                      
//=====================================================================================
GLuint      leaves_A_SHADER_VERTEX;                                                                                 
GLuint      leaves_A_SHADER_FRAGMENT;                                                                               
GLuint      leaves_A_SHADER;     
//-------------------------------------------------------------------------------------
GLuint      UNIFORM_LIGHT_POSITION_01_leaves_A;                                                                     

GLuint      UNIFORM_shininess_leaves_A;
GLuint      UNIFORM_ambient_leaves_A;
                                                                            
                                                                     
//-------------------------------------------------------------------------------------
GLuint      UNIFORM_PROJECTION_leaves_A;  
GLuint      UNIFORM_MODELVIEW_leaves_A; 
GLuint      UNIFORM_VIEW_leaves_A; 
GLuint      UNIFORM_MODELWORLD_leaves_A; 
GLuint      UNIFORM_VIEW_ROTATE_leaves_A;
//----
GLuint      UNIFORM_LIGHT_MATRIX_leaves_A;                 
//---- 
GLuint      UNIFORM_SHADOW_LIGHT_TEXTURE_MATRIX_leaves_A;

//-------------------------------------------------------------------------------------
GLuint      UNIFORM_ShadowTexture_leaves_A;       
GLuint      UNIFORM_TEXTURE_DOT3_leaves_A;  
GLuint      UNIFORM_TEXTURE_leaves_A; 

