#include <stdio.h>

int main(){
    char charachter;  
    int ul_counter = 0;
    int ol_counter = 0;

    char file_txt[25];
    char file_html[25];
    
    printf("Enter name of the source file (Max 25 Charachter): ");
    scanf("%s",file_txt);
    printf("Enter name of the output file (Max 25 Charachter): ");
    scanf("%s",file_html);

    FILE *filep = fopen(file_txt, "r");
    FILE *filehtml = fopen(file_html, "w");

    charachter = getc(filep);
    do
    {
        if (charachter == '*')
        {            
            fputs("<b>", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != '*');
                
            fputs("</b>", filehtml);
            charachter = getc(filep);
            
        }

        else if (charachter == '/')
        {
            fputs("<i>", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != '/');
                
            fputs("</i>", filehtml);
            charachter = getc(filep);
        }

        else if (charachter == '_')
        {
            fputs("<u>", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != '_');
                
            fputs("</u>", filehtml);
            charachter = getc(filep);
        }

        else if (charachter == '-')
        {
            fputs("<del>", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != '-');
                
            fputs("</del>", filehtml);
            charachter = getc(filep);
        }

        else if (charachter == '#')
        {
                charachter = getc(filep);
                if (charachter != '#')
                {
                    fputs("<h1>", filehtml);
                    do
                    {
                        putc(charachter, filehtml);
                        charachter = getc(filep);
                    } while (charachter != '\n');
                    fputs("</h1>", filehtml);
                }
                else
                {
                    charachter = getc(filep);
                    if (charachter != '#')
                    {
                        fputs("<h2>", filehtml);
                        do
                        {
                            putc(charachter, filehtml);
                            charachter = getc(filep);
                        } while (charachter != '\n');
                        fputs("</h2>", filehtml);
                    }
                    else
                    {
                        charachter = getc(filep);
                        fputs("<h3>", filehtml);
                        do
                        {
                            putc(charachter, filehtml);
                            charachter = getc(filep);
                        } while (charachter != '\n');
                        fputs("</h3>", filehtml);
                    }                    
                }
                fputc(charachter, filehtml);
                charachter = getc(filep); 
        }
        
        else if (charachter == '$')
        {
            fputs("<a href='", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != ' ');
            fputs("'>", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != ' ' && charachter != '\n' && charachter != EOF);
            fputs("</a>", filehtml);
            
        }

        else if (charachter == '!')
        {
            fputs("<img src='", filehtml);
            charachter = getc(filep);
            do
            {
                fputc(charachter, filehtml);
                charachter = getc(filep);
            } while (charachter != ' ' && charachter != '\n' && charachter != EOF);
            fputs("'>", filehtml);
        }

        else if (charachter == '.')
        {
            if (ul_counter == 0)
            {
                fputs("<ul>", filehtml);
                ul_counter++;
            }

            fputs("<li>", filehtml);
            charachter = getc(filep);
            
        }
        else if (charachter == ',')
        {
            if (ol_counter == 0)
            {
                fputs("<ol>", filehtml);
                ol_counter++;
            }

            fputs("<li>", filehtml);
            charachter = getc(filep);
            
        }
        
        else
        {
            if (ul_counter == 1 && charachter=='\n' && getc(filep)=='.')
            {
                fseek(filep, -1, SEEK_CUR);
                fputs("</li>", filehtml);
            }
            else if (ul_counter == 1 && charachter=='\n' && getc(filep)!='.')
            {
                fseek(filep, -2, SEEK_CUR);
                fputs("</li>", filehtml);
                fputs("</ul>", filehtml);
                ul_counter = 0;
            }
            if (ol_counter == 1 && charachter=='\n' && getc(filep)==',')
            {
                fseek(filep, -1, SEEK_CUR);
                fputs("</li>", filehtml);
            }
            else if (ol_counter == 1 && charachter=='\n' && getc(filep)!=',')
            {
                fseek(filep, -2, SEEK_CUR);
                fputs("</li>", filehtml);
                fputs("</ol>", filehtml);
                ol_counter = 0;
            }
            
            fputc(charachter, filehtml);
            charachter = getc(filep);
        }
        
    }while (charachter != EOF);
    return 0;
}