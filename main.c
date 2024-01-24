#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    // Diretório de origem (onde estão as fotos e vídeos)
    char *sourceDir = "C:\\Caminho\\Para\\Pasta\\Do\\Celular";

    // Diretório de destino (onde você deseja importar as fotos e vídeos)
    char *destinationDir = "C:\\Caminho\\Para\\Pasta\\No\\Computador";

    // Obter a data e hora atual
    time_t currentTime;
    struct tm *localTime;
    char defaultDate[20]; // YYYY-MM-DD HH:MM format
    time(&currentTime);
    localTime = localtime(&currentTime);
    strftime(defaultDate, sizeof(defaultDate), "%Y-%m-%d %H:%M", localTime);

    // Pedir ao usuário a data de início
    char startDate[20];
    printf("Digite a data e hora de início (padrão: %s): ", defaultDate);
    fgets(startDate, sizeof(startDate), stdin);
    
    // Usar a data e hora atual se o usuário não inserir nenhuma data
    if (strlen(startDate) == 1) { // Somente Enter foi pressionado
        strcpy(startDate, defaultDate);
    }

    // Abrir o diretório de origem
    DIR *dir = opendir(sourceDir);
    if (dir == NULL) {
        perror("Erro ao abrir o diretório de origem");
        return 1;
    }

    // Percorrer os arquivos no diretório de origem
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignorar entradas "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Obter informações sobre o arquivo
        struct stat fileStat;
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s\\%s", sourceDir, entry->d_name);

        if (stat(filePath, &fileStat) < 0) {
            perror("Erro ao obter informações do arquivo");
            continue;
        }

        // Verificar se a data de criação do arquivo está dentro do intervalo desejado
        // Implemente a lógica aqui para comparar as datas

        // Copiar o arquivo para o diretório de destino
        char destPath[1024];
        snprintf(destPath, sizeof(destPath), "%s\\%s", destinationDir, entry->d_name);
        if (rename(filePath, destPath) != 0) {
            perror("Erro ao copiar o arquivo");
            continue;
        }
        
        printf("Arquivo importado: %s\n", entry->d_name);
    }

    // Fechar o diretório de origem
    closedir(dir);

    return 0;
}