#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessUci.h"
#include "messages.h"
#include <unistd.h>

t_chessUci::t_chessUci(t_sharedData &theSharedData, int fd1, int fd2,  std::string theFile) : sharedData(theSharedData), filename(theFile)
{
   in[0] = fd1;
   in[1] = fd2;

   if (pipe(out))
   {
      perror("You have failed, pipe: ");
      exit(1);
   }

}

void t_chessUci::run()
{
   pid_t pid = fork();

   if (!pid)
   {
      close(in[1]);
      close(out[0]);

      dup2(in[0],0);
      dup2(out[1],1);

      std::cout<<"I am the child"<<std::endl;


      if (execvp(filename.c_str(),NULL))
      {
         perror("Fork and exec");
         exit(1);
      }
   }

   else
   {
      close (out[1]);
      close (in[0]);

      std::cout<<"I am the parent"<<std::endl;
      std::cout<<pid<<std::endl;

      t_message message;
      message.id = UCI_RESPONSE;
      char *buffer = (char *) malloc(100);
      size_t n = 100;

      FILE *blah2 = fdopen(out[0],"r");

      do
      {
         ssize_t b = getline(&buffer,&n,blah2);

         if (b == -1)
         {
            
            perror("getline:");
            if (feof(blah2))
               break;

            exit(1);
         }

         if (b)
         {

            char *temp = strdup(buffer);

            char *last;
            char *pch = strtok_r(temp," ",&last);

            /*
            if (0)
            //if (!strcmp(pch,"info") || !strcmp(pch,"option") || !strcmp(pch,"id"))
            {
               //printf("Info is %s %s\n",pch,buffer);
               free(temp);
               continue;
            }
            */



            printf("the string is %s\n",buffer);
            strncpy(message.uciResponse.response,buffer,39);
            message.uciResponse.response[39] = 0;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
               sharedData.gameCondition.notify_one();
            }

            free(temp);
         }

         if (b == 0)
         {
            printf("Nothing to print.. ");
         }

      }
      while (true);




   }
}
