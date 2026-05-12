#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define VERSION "v1.0.1"

typedef struct {
    char *nyelv;
    char *leiras;
    char *fnev;
    char *prog;
} Main;

Main programok[] = {
    {
        "c",
        "C forraskod sablon",
        "main.c",
        "#include <stdio.h>\n\nint main()\n"
        "{\n"   
        "   printf(\"Hello, World!\");\n"
        "\n"    
        "   return 0;\n"
        "}\n"
    },

    {
        "py",
        "Python forraskod sablon",
        "main.py",
        "def main():\n"
        "    print(\"Hello, World!\")\n"
        "\n"
        "main()\n"
    },

    {
        "java",
        "Java forraskod sablon",
        "Main.java",
        "public class Main {\n"
        "    public static void main(String[] args) {\n"
        "        System.out.println(\"Hello, World!\");\n"
        "    }\n"
        "}"
    },
    
    {
        "sh",
        "Bash forraskod sablon",
        "main.sh",
        "#!/usr/bin/env bash\n"
        "\necho 'Hello, World'\n"
    }
};

int nyelvek = sizeof(programok) / sizeof(programok[0]);


void help() {
    printf("'alap' %s\n", VERSION);
    puts("");
    printf("Hasznalat: alap <nyelv> [-k, --kapcsolo]\n");
    puts("");
    printf("Kapcsolok:\n");
    printf("  -h, --help      Megjeleniti ezt a sugot\n");
    printf("  -v, --version   Verzioszam\n");
    printf("  --stdout        Kiirja a sablon forraskodot a konzolra fajl letrehozasa nelkul\n");
    puts("");
    printf("Tamogatott nyelvek:\n");
    for (int i = 0; i < nyelvek; ++i) {
        printf("  %-10s - %s [%s]\n", programok[i].nyelv, programok[i].leiras, programok[i].fnev);
    }
}



int main(int argc, char *argv[]) {

    if (argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) 
    {
        help();
        return 0;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) 
    {
        printf("Az 'alap' program verzioja: %s\n", VERSION);
        return 0;
    }

    int stdout_mode = (argc == 3 && strcmp(argv[2], "--stdout") == 0);
    int id = -1;

    if (argc > 2 && (strcmp(argv[2], "--stdout") != 0)) 
    {
        fprintf(stderr, "Error! A masodik argumentum csak az '--stdout' lehet!");
        exit(1);
    }

    for (int i = 0; i < nyelvek; ++i) 
    {
        if (strcmp(argv[1], programok[i].nyelv) == 0) {
            id = i;
            break;
        }
    }

    if (id == -1) 
    {
        fprintf(stderr,"Error! nem tamogatott nyelv vagy kapcsolo: '%s'. Hasznald a --help vagy -h kapcsolokat a tamogatott nyelvek és kapcsolok listajahoz!\n", argv[1]);
        exit(2);
    }

    if (stdout_mode) 
    {
        printf("%s", programok[id].prog);
    } else 
    {
        if (access(programok[id].fnev, F_OK) == 0) 
        {
            fprintf(stderr,"Error: A fajl mar letre lett hozva: '%s'\n", programok[id].fnev);
            exit(3);
        }

        FILE *fajl = fopen(programok[id].fnev, "w");

        if (fajl) {
            fprintf(fajl, "%s", programok[id].prog);
            fclose(fajl);
            printf("# '%s' sikeresen letrehozva\n", programok[id].fnev);
        } 

        else 
        {
            fprintf(stderr,"Hiba tortent a fajl letrehozasakor!");
            exit(4);
        }
    }

    return 0;
}