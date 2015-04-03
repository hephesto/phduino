// commandline.h
//
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1250265171/1#1
//
// With some modifications.

#define CL_MAX_CMD_CHAR_NUM      10  // max length of the command string
#define CL_MAX_PARAMS_NUM        3 // max number of parameters
#define CL_MAX_PARAM_LEN 	 20 // max length of the parameters
#define CL_MAX_PARAM_CHAR_NUM    63 // max length of the parameters string
#define CL_MAX_CMD_LINE          80 // max length of the string (cmd + spacers + parameters)

char cmd_line[CL_MAX_CMD_LINE]; //entire input command line
char cmd_str[CL_MAX_CMD_CHAR_NUM]; //first word of command line
char cmd_parm_str[CL_MAX_PARAM_CHAR_NUM]; // rest of the line parsed out
int cmd_n_parms;    //populated size of cmd_parm up to max_params
char cmd_parm[CL_MAX_PARAMS_NUM][CL_MAX_PARAM_LEN]; //up to six parameters, of twelve characters each, separated by commas or spaces

unsigned int cl_i, cl_j, cl_k, cl_l;
char cl_in_ch;

char process_command_line(){

  if (Serial.available())
  {
    //Serial.println("Receiving....");

    delay(500);
    cl_i=0;
    cl_j=0;
    cl_k=0;
    cl_l=0;
    cmd_line[0]='\0';
    cmd_parm_str[0]='\0';					// clear param string
    cmd_n_parms=0;
    for (int x;x<CL_MAX_PARAMS_NUM;x++) 
    {
      cmd_parm[x][0]=0; // clear out previous parameters
    }

    //get a command line
    boolean first_word=true;
    while (Serial.available())
    {
      //cl_in_ch = upper(Serial.read());
      cl_in_ch = Serial.read();
      cmd_line[cl_i] = cl_in_ch;
      if (first_word && (cl_in_ch == ' '))
      {
        first_word=false;
        cmd_str[cl_i]='\0'; // add null terminator
        cl_i++;
        continue;
      }
      if (first_word) cmd_str[cl_i]=cl_in_ch;
      else // build cmd_parm_str
      { 
        cmd_parm_str[cl_j++]=cl_in_ch;
        if (cl_in_ch==' ' || cl_in_ch==',')
        { 
          cmd_parm[cl_k][cl_l]='\0';
          cl_k++;
          cl_l=0;
        }
        else
        {
          cmd_parm[cl_k][cl_l++]=cl_in_ch;
          cmd_n_parms++;
        }
      }
      cl_i++;
    } // end while

    if (!first_word)
    {			    // we had parameters so...
      cmd_parm_str[cl_j]='\0';   // null terminate param string
      cmd_parm[cl_k][cl_l]='\0';    // and the last param
      cmd_n_parms = cl_k+1;   // remember number of parameters (k doesn't get a chance to increment for last parm so add 1

        // we have a command line
      return 1;

    }
    else
    {
      cmd_str[cl_i]='\0';	  // terminate command str which normally happens when we start parsing parameters

      // we don't have a command line
      return 0;
    }

  }

}
