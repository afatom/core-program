
       


       int
       main(int argc, char* argv[])
       {
           

   

         

           

           

       

          

           printf("Listening for events stopped.\n");

           /* Close inotify file descriptor */

           close(fd);

           free(wd);
           exit(EXIT_SUCCESS);
       }
