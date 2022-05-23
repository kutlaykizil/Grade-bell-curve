#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct values {
    float mean,SD;
};

struct values calc(float data[],int count);
char** letters(float data[],struct values v,int count);
const char* getfield(char* line, int num);

int main(void) {
    int i,count=0;
    float data[128];
    char names[128][64];
    char line[1024];
    FILE* stream = fopen("GRADES.csv", "r");
    
    i=0;
    while (fgets(line, 1024, stream)) {
        char* tmp = strdup(line);
        data[i] = atof(getfield(tmp, 2));
        free(tmp);
        i++;
    }
    
    i=0;
    rewind(stream);
    while (fgets(line, 1024, stream)) {
        count++;
        char* tmp = strdup(line);
        strcpy(names[i], getfield(tmp, 1));
        free(tmp);
        i++;
    }
    fclose(stream);
    struct values v = calc(data,count);
    printf("\nClass average:%f,\nStandart deviation:%f\n", v.mean,v.SD);
    char** letter_grades = letters(data,v,count);
    FILE* outfile = fopen("Letter_Grades.csv", "w");
    for (i=0;i<count;i++){
        fprintf(outfile, "%s;%s\n", names[i], letter_grades[i]);
    }
    fclose(outfile);  
}   

struct values calc(float data[],int count) {
    struct values v;
    v.mean = 0;
    v.SD = 0;
    float sum = 0.0, mean = 0.0, SD = 0.0;
    int i;
    
    for (i = 0; i < count; ++i) {
        sum += data[i];
    }
    v.mean = sum / count;
    for (i = 0; i < count; ++i) {
        SD += (data[i] - v.mean) * (data[i] - v.mean);
    }
    v.SD = sqrt(SD/count);
    return v;
}

char** letters(float data[],struct values v,int count) {  
    
    char ** notes = malloc(100 * sizeof(char*));
    for (int i=0 ; i < count; ++i){
    notes[i] = malloc(count * sizeof(char));
    }
    
    int i;
    for (i=0;i<count;i++) {
        if (data[i] >= (v.mean+(2*v.SD)))
        strcpy(notes[i], "AA");

        else if (data[i] >= (v.mean+(1.5*v.SD)) && data[i] < (v.mean+(2*v.SD)))
        strcpy(notes[i], "BA");

        else if (data[i] >= (v.mean+(1*v.SD)) && data[i] < (v.mean+(1.5*v.SD)))
        strcpy(notes[i], "BB");

        else if (data[i] >= (v.mean+(0.5*v.SD)) && data[i] < (v.mean+(1*v.SD)))
        strcpy(notes[i], "CB");

        else if (data[i] >= (v.mean) && data[i] < (v.mean+(0.5*v.SD)))
        strcpy(notes[i], "CC");

        else if (data[i] < (v.mean) && data[i] >= (v.mean-(0.5*v.SD)))
        strcpy(notes[i], "DC");

        else if (data[i] < (v.mean-(0.5*v.SD)) && data[i] >= (v.mean-(1*v.SD)))
        strcpy(notes[i], "DD");

        else if (data[i] < (v.mean-(1*v.SD)) && data[i] >= (v.mean-(1.5*v.SD)))
        strcpy(notes[i], "FD");

        else if (data[i] <= (v.mean-(1.5*v.SD)))
        strcpy(notes[i], "FF");

        else 
        printf("\nSOMETHINGS WRONG \n");
    }
/*
    for (i=0;i<count;i++) {
        printf("%s\n",notes[i]); //to print the letters
    }
*/       
    return notes;
}

const char* getfield(char* line, int num) {
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}