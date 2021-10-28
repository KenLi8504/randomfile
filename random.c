#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int getRandNum(int data) {
    int random;
    int error = read(data, &random,4);
    if(error == -1) {
        printf("PROBLEM RUH ROH\n");
        printf("The problem is %s\n",strerror(error) );
        return 0;
    }
    return random;
}

int main() {
    int data = open("/dev/random213",O_RDONLY);
    int array[10];
    int err;

    printf("\nGenerating random numbers from invalid file:\n");
    for(int i = 0; i < 10; i++){
        array[i] = getRandNum(data);
        printf("\trandom %d: %u\n",i, array[i]);
    }

    data = open("/dev/random",O_RDONLY);

    printf("\nGenerating random numbers from valid file:\n");
      for(int i = 0; i < 10; i++){
        array[i] = getRandNum(data);
        printf("\trandom %d: %d\n",i, array[i]);
    }

    printf("\nWriting numbers to file...\n\n");
    int file = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if(file==-1){
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    err = write(file, array, 40);
    if(err==-1){
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    printf("Reading numbers from file...\n\n");
    // open out.txt
    file = open("test.txt",O_RDONLY);
    if(err == -1) {
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    int arr2[10];
    err = read(file,arr2,40);
    if(err == -1) {
        printf("Error:\n");
        printf("%s\n", strerror(errno));
        return 0;
    }

    printf("Checking if the number is still the same:\n");
      for(int i = 0; i < 10; i++){
        printf("\trandom %d: %d\n",i, arr2[i]);
    }

    return 0;
}
