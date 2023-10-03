#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Options
{
    char *text;
    int next_scene;
} Options;

typedef struct Scene
{
    int id;
    char *text;
    int num_options;
    struct Options *option_number;
} Scene;

void free_scene(Scene *scene)
{
    if (scene)
    {
        free(scene->text);

        if (scene->option_number)
        {
            for (int i = 0; i < scene->num_options; i++)
            {
                free(scene->option_number[i].text);
            }
            free(scene->option_number);
        }

        free(scene);
    }
}

int main()
{
    FILE *file = fopen("scen.txt", "r");
    if (!file)
    {
        printf("Failed to open file.\n");
        return 1;
    }

    Scene *scenes[100]; // Assuming there are at most 100 scenes
    int scene_count = 0;

    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "//") == NULL)
        {
            continue;
        }
        Scene *scene = (Scene *)malloc(sizeof(Scene));
        scene->text = NULL;
        scene->option_number = NULL;

        char *token = strtok(line, "/"); // Change the delimiter to "/"
        scene->id = atoi(token);

        token = strtok(NULL, "/");
        scene->text = strdup(token);

        token = strtok(NULL, "/");
        scene->num_options = atoi(token);

        if (scene->num_options > 0)
        {
            Options *options = (Options *)malloc(scene->num_options * sizeof(Options));

            for (int i = 0; i < scene->num_options; i++)
            {
                token = strtok(NULL, "/");
                options[i].text = strdup(token);
                // printf("!#%s\n", options[i].text);

                token = strtok(NULL, "/");
                options[i].next_scene = atoi(token);
                // printf("!!%d\n", options[i].next_scene);
            }
            scene->option_number = options;
        }

        // token = strtok(NULL, "/");
        // options->next_scene = atoi(token);

        scenes[scene_count++] = scene;
    }

    fclose(file);

    // Now you can access the parsed scenes and their information
    // printf("!!%d\n", scene_count);
    // for (int i = 0; i < scene_count; i++)
    // {
    int i = 0;
    int opt = 0;
     while (opt != -1)
    {
    Scene *scene = scenes[i];
    // Options *options;
    printf("Scene %d: %s\n", scene->id, scene->text);
    printf("Options number: %d\n", scene->num_options);
    for (int j = 0; j < scene->num_options; j++)
    {
        printf("Option %d: %s\n", j + 1, scene->option_number[j].text);
        printf("Next Scene: %d\n", scene->option_number[j].next_scene);
    }
    
    printf("/////////////\n");


    // while (opt != -1)
    // {
        // Scene *scene = scenes[i];
        scanf("%d", &opt);
        
        printf("Вы выбрали вариант %d\n", opt);
       
        // for (int j = 0; j < scene->num_options; j++)
        // {
        //     if (opt == j + 1)
        //     {
                //  printf("???????? %d\n", scene->option_number[opt-1].next_scene);
                i = scene->option_number[opt-1].next_scene;
        //     }
        // }
        // printf("???? %d \n", i);
        // Scene *scene = scenes[i-1];
        i -= 1;
        // printf("Scene %d: %s\n", scene->id, scene->text);
        // printf("Options number: %d\n", scene->num_options);
        // for (int j = 0; j < scene->num_options; j++)
        // {
        //     printf("Option %d: %s\n", j + 1, scene->option_number[j].text);
        //     printf("Next Scene: %d\n", scene->option_number[j].next_scene);
        // }
    }

    // Free allocated memory
    for (int i = 0; i < scene_count; i++)
    {
        free_scene(scenes[i]);
    }

    return 0;
}
