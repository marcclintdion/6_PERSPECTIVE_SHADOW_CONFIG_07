    leaves_A_SHADER = glCreateProgram();                                                                                     
        //----------------------------------------------------                                                                  
    const GLchar *vertexSource_leaves_A =                                                                                    

      " #define highp                                                                                                                           \n" 
      
      
      "    attribute      vec4 position;                                                                                                        \n" 
      "    attribute      vec2 textureCoords;                                                                                                   \n" 
      "    //-------------------------------------------------                                                                                  \n"     
      "    uniform  highp vec4  light_POSITION_01;                                                                                              \n" 
      
      "    uniform        mat4  modelView;                                                                                                       \n" 
      "    uniform        mat4  projection;                                                                                                      \n" 
      
      "    uniform        mat4  view;                                                                                                       \n"         
      "    uniform        mat4  modelWorld;                                                                                                       \n"         
      
      "    uniform        mat4  view_Rotate;                                                                                                       \n"            
      //-----

      "      uniform        mat4  light_TextureMatrix;                                                                                               \n"        
      //-----
      "      uniform        mat4  lightMatrix;                                                                                                    \n" 
      "      varying highp  vec4  shadowTexcoord;                                                                                                 \n"       
    //--------------------------------------------
   
   
    //-------------------------------------------------                                                                
    "      varying highp  vec4  lightPosition_PASS;                                                                                             \n" 
    "      varying highp  vec2  varTexcoord;                                                                                                    \n" 
    //--------------------------------------------

    //==================================================================================================================================
    
    " void main()                                                                                                                               \n" 
    " {                                                                                                                                         \n" 
                 //-------------------------------------------------------------------------------    
    "            shadowTexcoord          =   light_TextureMatrix * modelView * position;                                                         \n" 
                 //-------------------------------------------------------------------------------

    "            varTexcoord             = textureCoords;                                                                                       \n" 
    "            lightPosition_PASS      = normalize(lightMatrix * light_POSITION_01);                                                          \n" 
    
    "            gl_Position             = projection * view * view_Rotate *  modelWorld * position;                                                                                \n" 
    
    " } \n";   
    
    //===================================================================================================================================                 

    const GLchar *fragmentSource_leaves_A =                                                                                  

    "#ifdef GL_ES                                                                                                                               \n" 
    "#else                                                                                                                                      \n" 
    "#define highp                                                                                                                              \n" 
    "#endif                                                                                                                                     \n" 
    //-----------------------------------------------------------------------------------------------------------------------------------
    "     uniform sampler2D    NormalMap;                                                                                                       \n" 
    "             highp  vec3  NormalTex;                                                                                                       \n" 
    "             highp float  NdotL1;                                                                                                          \n" 
    //--------------------------------------------
    "    uniform sampler2D   ShadowTexture;                                                                                                     \n"   
    "    varying highp vec4  shadowTexcoord;                                                                                                    \n"       
    //--------------------------------------------
    "     uniform sampler2D    Texture1;                                                                                                        \n"     
   
    "     uniform highp float  shininess;                                                                                                       \n"    
    "     uniform highp float  ambient;                                                                                                         \n" 
    //--------------------------------------------                                                                      
    "     varying highp  vec4  lightPosition_PASS;                                                                                              \n" 
    "     varying highp  vec2  varTexcoord;                                                                                                     \n" 
    //--------------------------------------------                                                                       
    "             highp  vec4  tempColor;                                                                                                       \n" 
    "             highp  vec4  specular;                                                                                                        \n"     
    //-------------------------------------------- 
                                                                
    //=======================================================================================================================                      
   
   "void main()                                                                                                                                 \n" 
    "{                                                                                                                                          \n" 
        "       NormalTex       =  texture2D(NormalMap,  varTexcoord.xy).xyz;                                                                   \n" 
        "       NormalTex       =  normalize((NormalTex  - 0.5));                                                                               \n" 
        "       NdotL1          =  dot(NormalTex, lightPosition_PASS.xyz);                                                                      \n"   
                //----------------------------------------------------------------------------                                                   
                //---------------------------------------------------------------------------------------------------------------------
      "       highp float bias =  shininess;                                                          \n"         
//        "       highp float bias =  shininess * tan(acos(NdotL1));                                                          \n" 
//        "       bias             =  clamp(bias, 0.0, 0.1);                                                          \n"               
 
        
        "       highp float comp = (shadowTexcoord.z / shadowTexcoord.w) - bias;                                                          \n" 
        "       highp float depth_PowerVR = texture2DProj(ShadowTexture, shadowTexcoord).r;                                                     \n" 
        "       highp float shadowVal = comp <= depth_PowerVR ? 1.0 : 0.4;                                                                      \n" 
                //---------------------------------------------------------------------------------------------------------------------

                //----------------------------------------------------------------------------                                           
 //     "       tempColor       =  texture2D(Texture1, varTexcoord.xy);                                                                         \n" 
//_THE_ABOVE_MIGHT_BE_BETTER_FOR_LEAVES
       "       tempColor       =  pow(NdotL1, 50.0) * texture2D(Texture1, varTexcoord.xy) + texture2D(Texture1, varTexcoord.xy);               \n" 

                //----------------------------------------------------------------------------   
//        "       specular        =  (highp vec4(1.0, .7, .2, 1.0) * pow(NdotL1,  shininess) * tempColor) * shadowVal * shadowVal;                \n" 
        "       gl_FragColor    =  texture2D(Texture1, varTexcoord.xy) * NdotL1 * shadowVal + highp vec4(0.2, 0.2, 0.2, 0.2);                                                                                 \n" 
    "}\n";

    
      //--------------------------------------------------------------------------------------------------                    

        leaves_A_SHADER_VERTEX = glCreateShader( GL_VERTEX_SHADER);                                                          
        glShaderSource( leaves_A_SHADER_VERTEX, 1, &vertexSource_leaves_A, NULL );                                        
        glCompileShader( leaves_A_SHADER_VERTEX);                                              //glShaderBinary                              
        //----------------------------------------------------                                                                  
        leaves_A_SHADER_FRAGMENT = glCreateShader( GL_FRAGMENT_SHADER);                                                      
        glShaderSource( leaves_A_SHADER_FRAGMENT, 1, &fragmentSource_leaves_A, NULL );                                    
        glCompileShader(leaves_A_SHADER_FRAGMENT);                                              //glShaderBinary                                                                             
        //--------------------------------------------------------------------------------------------------                    
        glAttachShader( leaves_A_SHADER, leaves_A_SHADER_VERTEX );                                                        
        glAttachShader( leaves_A_SHADER, leaves_A_SHADER_FRAGMENT );                                                      
        //--------------------------------------------------------------------------------------------------                    
        glBindAttribLocation(leaves_A_SHADER,   0, "position");                                                              
        glBindAttribLocation(leaves_A_SHADER,   1, "normal");                                                            
        glBindAttribLocation(leaves_A_SHADER,   2, "textureCoords");                                                             
        //--------------------------------------------------------------------------------------------------                    
        glDeleteShader( leaves_A_SHADER_VERTEX);                                                                             
        glDeleteShader( leaves_A_SHADER_FRAGMENT);                                                                           
        glLinkProgram(leaves_A_SHADER);                                                                                      
        //--------------------------------------------------------------------------------------------------                    
        UNIFORM_MODELVIEW_leaves_A                          = glGetUniformLocation(leaves_A_SHADER, "modelView");                  
        UNIFORM_PROJECTION_leaves_A                         = glGetUniformLocation(leaves_A_SHADER, "projection");  
        
        UNIFORM_VIEW_leaves_A                               = glGetUniformLocation(leaves_A_SHADER, "view");                  
        UNIFORM_MODELWORLD_leaves_A                         = glGetUniformLocation(leaves_A_SHADER, "modelWorld");          
        
        UNIFORM_VIEW_ROTATE_leaves_A                         = glGetUniformLocation(leaves_A_SHADER, "view_Rotate");             
        //-------------------------------
        UNIFORM_SHADOW_LIGHT_TEXTURE_MATRIX_leaves_A        = glGetUniformLocation(leaves_A_SHADER, "light_TextureMatrix");                                                  
        //-------------------------------      
        UNIFORM_LIGHT_MATRIX_leaves_A                       = glGetUniformLocation(leaves_A_SHADER, "lightMatrix");                
        //----------------------------- 
        UNIFORM_LIGHT_POSITION_01_leaves_A                  = glGetUniformLocation(leaves_A_SHADER, "light_POSITION_01");          
        UNIFORM_shininess_leaves_A                          = glGetUniformLocation(leaves_A_SHADER, "shininess");  
       
        UNIFORM_ambient_leaves_A                            = glGetUniformLocation(leaves_A_SHADER, "ambient");  
          
        UNIFORM_ShadowTexture_leaves_A                      = glGetUniformLocation(leaves_A_SHADER, "ShadowTexture");           
        UNIFORM_TEXTURE_DOT3_leaves_A                       = glGetUniformLocation(leaves_A_SHADER, "NormalMap");                  
        UNIFORM_TEXTURE_leaves_A                            = glGetUniformLocation(leaves_A_SHADER, "Texture1");  
