#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    char str1[6], str2[2], str3[20];
    char c;
    int CharCount(char *filename);
    int WordCount(char *filename);
    int LineCount(char *filename);
    int ComplexCount(char *filename);
    do{
        system("cls");
        printf("\n/**************��ӭʹ��WordCount**************/\n\n");
        printf("\t\t��Ϣ��ȫ��2����\n");
        printf("\t\t3216005217\n");
        printf("\t\t��ܰ��\n\n");
        printf("/*******************************************/\n\n");
        printf("����ʽΪ��wc.exe [parameter] [file_name]��\n\n");
        printf("�������û����");
        while((c=getchar())!='\n'){
            scanf("%s%s%s",str1,str2,str3);
        }
        if(str2[1]=='c'||str2[1]=='w'||str2[1]=='l'||str2[1]=='a'){
            switch(str2[1]){
                case 'c':CharCount(str3);
                         system("pause");
                         break;
                case 'w':WordCount(str3);
                         system("pause");
                         break;
                case 'l':LineCount(str3);
                         system("pause");
                         break;
                case 'a':ComplexCount(str3);
                         system("pause");
                         break;
            }
        }else{
            printf("\n�ݲ�֧��%c����\n",str2[1]);
        }
    }while(str2[1]=='c'||str2[1]=='w'||str2[1]=='l'||str2[1]=='a');
    getchar();
    return 0;
}
// �����ļ����ַ���
int CharCount(char *filename){
    FILE * fp;
    int charCount=0;
    char a[688];
    if((fp=fopen(filename,"r"))==NULL){
        printf("�޷����ļ�\n");
    }else{
        while(!feof(fp)){
            a[charCount]=fgetc(fp);
            if(isalnum(a[charCount])){
                //putchar(a[i]);
                charCount++;
            }
        }
        printf("\n���ļ����ַ���Ϊ��%d\n\n",charCount);
    }
    return charCount;
}
//�����ļ��ĵ�����
int WordCount(char *filename){
    FILE * fp;
    int wordCount=0, word=0;
    char c;
    if((fp=fopen(filename,"r"))==NULL){
        printf("�޷����ļ�\n");
    }else{
        c=fgetc(fp);
        while(c!=EOF){
            if((!isalpha(c))&&c!='-')  word=0;
            else if(word==0){
                word=1;
                wordCount++;
            }
             c=fgetc(fp);
        }
        printf("\n���ļ��ĵ�����Ϊ��%d\n\n",wordCount);
    }
    return wordCount;
}

//�����ļ�������
int LineCount(char *filename){
    FILE * fp;
    int lineCount=0, line=0;
    char c;
    if((fp=fopen(filename,"r"))==NULL){
        printf("�޷����ļ�\n");
    }else{
        while(!feof(fp)){
            c=fgetc(fp);
            if(isalnum(c)||c=='{'||c=='}')  line=1;
            else if(c=='\n'){
                if(line==1){
                    lineCount++;
                    line=0;
                }else  line=0;
            }
        }
        if(c==EOF && line==1) lineCount++;
        printf("\n���ļ�������Ϊ��%d\n\n",lineCount);
    }
    return lineCount;
}

int ComplexCount(char *filename){
    FILE * fp;
    int emptyLineCount, codeLineCount, commentLineCount;
    int EmptyLineCount(char *filename);
    int CodeLineCount(char *filename);
    int CommentLineCount(char *filename);
    if((fp=fopen(filename,"r"))==NULL){
        printf("�޷����ļ�\n");
    }else{
        emptyLineCount=EmptyLineCount(filename);
        codeLineCount=CodeLineCount(filename);
        commentLineCount=CommentLineCount(filename);
        printf("\n���ļ��Ŀ�������Ϊ��%d\n",emptyLineCount);
        printf("���ļ��Ĵ���������Ϊ��%d\n",codeLineCount);
        printf("���ļ���ע��������Ϊ��%d\n\n",commentLineCount);
    }
    return 0;
}

int EmptyLineCount(char *filename){
    FILE * fp;
    char c;
    int empty=1, lineCount=0;
    fp=fopen(filename,"r");
    while(!feof(fp)){
        c=fgetc(fp);
        if(c!=' '&&c!='t'&&c!='{'&&c!='}'&&c!='\n'){
           empty=0;
        }
        else if(c=='\n'){
            if(empty==0) empty=1;
            else     lineCount++;
        }
    }
    return lineCount;
}

int CodeLineCount(char *filename){
    FILE * fp;
    char c;
    int code=0, lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(isalnum(c)||c=='\n'){
            while(c!='\n'){
                code++;
                c=fgetc(fp);
            }
            if(code>=2){
                lineCount++;
                c=fgetc(fp);
            }
            else c=fgetc(fp);
        }else if(c=='/'){
            c=fgetc(fp);
            if(c=='/'){
                c=fgetc(fp);
                while(c!='\n')  c=fgetc(fp);
            }else if(c=='*'){
                c=fgetc(fp);
                while(c!='*'&&(c=fgetc(fp)!='/')) c=fgetc(fp);
                c=fgetc(fp);
            }
            c=fgetc(fp);
        }else c=fgetc(fp);
    }
    return lineCount;
}

int CommentLineCount(char *filename){
    FILE * fp;
    char c;
    int lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c=='/'){
            c=fgetc(fp);
            if(c=='/'){
                lineCount++;
                c=fgetc(fp);
                while(c!='\n') c=fgetc(fp);
            }else if(c=='*'){
                c=fgetc(fp);
                if(c=='\n'){
                    lineCount++;
                    c=fgetc(fp);
                }else if(c=='*'&&(c=fgetc(fp)!='/')){
                    lineCount++;
                    c=fgetc(fp);
                }
            }
        }
        c=fgetc(fp);
    }
    return lineCount;
}
