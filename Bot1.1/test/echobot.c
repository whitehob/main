#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <telebot.h>

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

int main(int argc, char *argv[])
{
    printf("Welcome to Echobot\n");

    FILE *fp = fopen(".token", "r");
    if (fp == NULL)
    {
        printf("Failed to open .token file\n");
        return -1;
    }

    char token[1024];
    if (fscanf(fp, "%s", token) == 0)
    {
        printf("Failed to read token\n");
        fclose(fp);
        return -1;
    }
    printf("Token: %s\n", token);
    fclose(fp);

    telebot_handler_t handle;
    if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
    {
        printf("Telebot create failed\n");
        return -1;
    }

    telebot_user_t me;
    if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
    {
        printf("Failed to get bot information\n");
        telebot_destroy(handle);
        return -1;
    }

    printf("ID: %d\n", me.id);
    printf("First Name: %s\n", me.first_name);
    printf("User Name: %s\n", me.username);

    telebot_put_me(&me);

    int index, count, offset = -1;
    telebot_error_e ret;
    telebot_message_t message;
    telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};
    int flag = 0;
    while (1)
    {
        telebot_update_t *updates;
        ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates, &count);
        if (ret != TELEBOT_ERROR_NONE)
            continue;
        printf("Number of updates: %d\n", count);
        for (index = 0; index < count; index++)
        {
            message = updates[index].message;
            if (message.text)
            {
                printf("%s: %s \n", message.from->first_name, message.text);
                if (strstr(message.text, "/dice"))
                {
                    telebot_send_dice(handle, message.chat->id, false, 0, "");
                }

                else
                {
                    char str[4096];
                    if (strstr(message.text, "/start"))

                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Hапиши \"начать\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 99;
                    }
                    // char str3[150];
                    // // char str4[100];
                    // ----------------------------------------FIRST SCENE
                    if (strstr(message.text, "Начать") || strstr(message.text, "начать"))
                    {

                        snprintf(str, SIZE_OF_ARRAY(str), "Ты просыпаешься на холодном полу. Голова гудит, сознание спутанно...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) \"Что это за место?\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Попробовать вспомнить, что произошло с тобой");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "3) Попытаться встать");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 1;
                    }

                    else if (strstr(message.text, "1") && flag == 1)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Осмотревшись ты замечаешь стальную конструкцию, которая вмонтирована в потолок, похожую на устройство для ухода за людьми. Само место предсталяет из себя комнату с тремя столами, на одном из которых лежит другой человек. Ты не помнишь, кто это. Быть может, это член команды? Какой команды... Кто я?");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Попробовать вспомнить, что произошло с тобой");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "3) Попытаться встать");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 1;
                    }
                    else if (strstr(message.text, "2") && flag == 1)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Мысли спутанны... В голове только вспышки света и отблески тревожных ламп. Более - ничего. Пока ничего...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) \"Что это за место?\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "3) Попытаться встать");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 1;
                    }
                    else if (strstr(message.text, "3") && flag == 1)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Тело сильно ослаблено... Встать пока не получается. Ты замечаешь стальную конструкцию, которая вмонтирована в потолок, похожую на устройство для ухода за людьми.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 3;
                    }
                    if (flag == 3)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Кроме этого, ты замечаешь лестницу в дальнем углу комнаты и люк в потолке.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) \"Болит голова...\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Ползти к лестнице ");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 4;
                    }
                    else if (strstr(message.text, "1") && flag == 4)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "После твоих слов, железные руки на потолке начинают движение, устремляются к тебе и замирают прямо перед твоим лицом. Ты видишь в самом центре руки отверстие, где стоит стакан воды и 2 таблетки. Ты уверен, что они от головной боли, так как раньше принимал их. Теперь, можно ползти к лестнице");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Ползти к лестнице ");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 3;
                       
                    }
                    else if (strstr(message.text, "2") && flag == 4)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Ты пробираешься по холодному полу к лестнице. Начинаешь пытаться забраться на неё, но сил явно нехватает. Устал. Нужно поесть и как следует отдохнуть... Кажется, стоит попросить эту штуку дать тебе еды.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 5;
                    }
                    else if ((strstr(message.text, "дай поесть") || strstr(message.text, "хочу есть") || strstr(message.text, "дай еды") || strstr(message.text, "Дай еды") || strstr(message.text, "дай пожрать") || strstr(message.text, "дай похавать") || strstr(message.text, "штука дай еды") || strstr(message.text, "Штука, дай еды") || strstr(message.text, "Штука дай еды") || strstr(message.text, "дать еды") || strstr(message.text, "дайте еды") || strstr(message.text, "дайте пожалуйста еды") || strstr(message.text, "Дайте пожалуйста еды")) && flag == 5)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Руки моментально откликаются, поднося тебе пакет с какой-то серой питательной субстанцией. Вкус вполне приятный, хоть ты и не до конца понимаешь, что это. Ты хорошо уталяешь голод. Руки бережно перекладывают тебя на твою кровать и ты засыпаешь...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 6;
                    }
                    if (flag == 6 || (strstr(message.text, "2") && flag == 6))
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Проснувшись ты чувствуешь в себе прилив сил. Ты можешь стоять, а слегка пошатываясь, даже ходить. Может, стоит узнать, что это за люк наверху...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Направиться к люку");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Осмотреть остальные \"кровати\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 7;
                    }

                    else if (strstr(message.text, "1") && flag == 7)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Да, сейчас сил точно больше, чем в прошлый раз! Доходишь до лестницы и пробуешь подняться. Получается!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 8;
                    }
                    else if (strstr(message.text, "2") && flag == 7)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "На одной из кроватей нет ничего. Она кажется прибранной и застеленной. На второй кровати лежит сухое тело.Черты лица различить сложно тело не издает никаких запахов, однако очевидно, что это давно не живой человек.Присмотревшись ты замечаешь нашивку на груди \"Семенова\". Еще бы вспомнить, кто такая, эта Семенова... Быть может, за этим люком будет больше ответов.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Направиться к люку");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 7;
                    }
                    if (flag == 8)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Теперь ты хотя бы можешь ползти по лестнице. Прогресс! Доползя до самого верха, ты видишь отпорное колесо, и надпись \"Left - Open. Right - Close.\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Крутить влево");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Крутить вправо");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 9;
                    }
                    else if (strstr(message.text, "1") && flag == 9)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Попытка была неплохая, но сдвинуть колесо с места пока не получается. Нужно подумать, что делать дальше.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 10;
                    }
                    else if (strstr(message.text, "2") && flag == 9)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Не поддается... Кажется, когда-то стоило все-таки начать учить этот английский...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Крутить влево");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 9;
                    }

                    if (flag == 10)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Судя по всему, вариантов у нас не много.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Слезть и набираться сил, чтобы попытаться завтра. Или не завтра, но после отдыха. Мышцы кажутся еще ослабленными...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) Попытаться покрутить изо всех оставшихся сил!!!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "3) Попросить железные робо-руки открыть тебе этот чертов люк");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 11;
                    }
                    else if (strstr(message.text, "1") && flag == 11)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Снова выпив чудодейственной субстанции тебя клонит в сон и ты быстро уходишь в царство морфея, набираться сил");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 15;
                    }
                    else if (strstr(message.text, "2") && flag == 11)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Ты кряхтишь, ощущение, что сами кости начинают скрипеть и трещать под твоими усилиями, однако это ни к чему не приводит. Сил слишком мало. Руки совсем не держат, как и ноги. Ты срываешься с лестницы и бьешься головой об пол. Глаза застелает пелена и ты засыпаешь. Может, все это и был сон...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 6;
                        continue;
                    }
                    else if (strstr(message.text, "3") && flag == 11)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "\"Открыть люк!\" Ты видишь как железные клешни вцепляются в люк и с легкостью проворачивают колесо. Кажется, нужно было набраться сил и открыть люк самому не составило бы проблем.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 12;
                    }
                    if (flag == 15)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Проснувшись ты полон сил и энергии открыть этот люк и вылезти из этой комнаты!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Вперед!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 16;
                    }
                    else if (strstr(message.text, "1") && flag == 16)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Ты забираешься на лестницу, пытаешься открутить это колесо. Сильнее... ЕЩЕ! Руки соскальзывают... Вытираешь их об рубашку и снова пытаешься провернуть колесо... Слышишь легкий скрип и вдруг колесо поддается и ты видишь зеленый индикатор открытого положения.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 17;
                    }

                    if (flag == 12)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Что делаешь дальше?");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Попросить еще еды и отдохнуть, набраться сил и потом ползти в следующую комнату. Судя по всему, спешка тут ни к чему.");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "2) ЛЕЗЕМ В ОТКРЫТЫЙ ЛЮК!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 13;
                    }
                    else if (strstr(message.text, "1") && flag == 13)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Снова выпив чудодейственной субстанции тебя клонит в сон и ты быстро уходишь в царство морфея, набираться сил");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 18;
                    }
                    else if (strstr(message.text, "2") && flag == 13)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Ты чувствуешь легкое чувство голода, но любопытство сильнее...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        flag = 17;
                    }
                    if (flag == 18)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Проснувшись ты полон сил и энергии чтобы исследовать этот люк и вылезти из этой комнаты!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "1) Вперед!");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");

                        flag = 17;
                    }
                    // snprintf(str, SIZE_OF_ARRAY(str), "<i>%d</i>", flag);

                    if (flag == 17)
                    {
                        snprintf(str, SIZE_OF_ARRAY(str), "Поздравляю! Вы прошли первый уровень моего увлекательного (надеюсь) квеста! Отзывы, придложения и пожелания оставьте при себе, мне и так хорошо. До новых встреч...");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "\n");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "Штука, пишите все в директ, конечно!)");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                        snprintf(str, SIZE_OF_ARRAY(str), "P.S. Для перезапуска, напиши \"начать\"");
                        ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, 0, "");
                    }

                    // else if (strstr(message.text, "Кто самая лучшая девушка в мире?"))
                    // {
                    //     snprintf(str, SIZE_OF_ARRAY(str), "Staisy Johnson - @staisy_angel");
                    //     flag = 1;
                    // }

                    else
                    {
                        if (flag == 0)
                            snprintf(str, SIZE_OF_ARRAY(str), "<i>Некорректный ввод, %s </i>", message.from->first_name);
                    }
                }
                if (ret != TELEBOT_ERROR_NONE)
                {
                    printf("Failed to send message: %d \n", ret);
                }
            }
            offset = updates[index].update_id + 1;
        }
        telebot_put_updates(updates, count);

        sleep(1);
    }

    telebot_destroy(handle);

    return 0;
}
// hello