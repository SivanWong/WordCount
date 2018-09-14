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
    //�γ�һ��ѭ��
    do{
        system("cls");
        printf("\n/**************��ӭʹ��WordCount**************/\n\n");
        printf("����ʽΪ��wc.exe [parameter] [file_name]��\n\n");
        printf("�������û����");
        while((c=getchar())!='\n'){
            scanf("%s%s%s",str1,str2,str3);  //����洢�����ָ��
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
    char c;
    //���ж��ļ��ܷ��
    if((fp=fopen(filename,"r"))==NULL){
        printf("�޷����ļ�\n");
    }else{
        while(!feof(fp)){
            c=fgetc(fp);  //�����ļ��е��ַ�
            if(isalnum(c)){   //�ж��ַ��Ƿ�ΪӢ�ġ������ַ�
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
            if(isalpha(c)) //�ж��ַ��Ƿ�ΪӢ���ַ�
                word=1;    //���Ϊһ�����ʵĿ�ʼ
            else if(c=='-'&&word==1){
                word=1;
            }else{
                if(word==1){
                    wordCount++;
                    word=0;  //һ�����ʽ���������Ϊ0
                }
            }
            c=fgetc(fp);
        }
        if(c==EOF&&word==1) //Ϊ�˷�ֹ�ļ�������ǰû�г�Ӣ���ַ������ӷ�������ַ�����û�м���
            wordCount++;
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
        c=fgetc(fp);   //�����ļ��е��ַ�
        while(c!=EOF){
            if(c!=' '&&c!='\t'&&c!='\v'&&c!='\r'&&c!='\n')
                line=1;   //���һ�еĿ�ʼ
            else if(c=='\n'){
                if(line==1){
                    lineCount++;
                    line=0;  //һ�н���������Ϊ0
                }else
                    line=0;
            }
            c=fgetc(fp);
        }
        if(c==EOF && line==1)  //Ϊ�˷�ֹ���һ��û�л��ж�û�������з�����û�м���
            lineCount++;
        printf("\n���ļ�������Ϊ��%d\n\n",lineCount);
    }
    return lineCount;
}

//�����ļ������ӵ����ݣ����С������С�ע���У�
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

//�����ļ��Ŀ�������
int EmptyLineCount(char *filename){
    FILE * fp;
    char c;
    int empty=1, lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c!=' '&&c!='t'&&c!='\v'&&c!='\r'&&c!='\n'&&c!='{'&&c!='}')
           empty=0;     //����ⲻ�ǿ���
        else if(c=='\n'){
            if(empty==0)
                empty=1;   //����Ϊ1
            else{
                lineCount++;
                empty=0;
            }
        }
        c=fgetc(fp);
    }
    if(c==EOF&&empty==1)  //Ϊ�˷�ֹ���һ��û�л��ж�û�������з�����û�м���
        lineCount++;
    return lineCount;
}

//�����ļ��Ĵ���������
int CodeLineCount(char *filename){
    FILE * fp;
    char c;
    int code=0, codeline=0, lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(isalnum(c)){
            if(code==1){  //�ж��Ƿ�����һ����Ч�ַ�
                codeline=1;  //���Ϊ�����еĿ�ʼ
                code=0;
            }else
                code=1;
        }else if(c=='\n'&&codeline==1){
            lineCount++;
            code=0;
            codeline=0;
        }else if(c=='/'){   //�ų�ע����
            c=fgetc(fp);
            if(c=='/'){
                c=fgetc(fp);
                while(c!='\n')  c=fgetc(fp);
            }else if(c=='*'){
                c=fgetc(fp);
                while(c!='/')
                    c=fgetc(fp);
                c=fgetc(fp);
            }
        }
        c=fgetc(fp);
    }
    if(c==EOF&&codeline==1)  //Ϊ�˷�ֹ���һ��û�л��ж�û�������з�����û�м���
        lineCount++;
    return lineCount;
}

//�����ļ���ע��������
int CommentLineCount(char *filename){
    FILE * fp;
    char c;
    int lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c=='/'){  //�����ж��Ƿ�Ϊע����
            c=fgetc(fp);
            if(c=='/'){  //����ע��
                lineCount++;
                c=fgetc(fp);
                while(c!='\n') c=fgetc(fp);
            }else if(c=='*'){  //����ע��
                lineCount++;
                c=fgetc(fp);
                while(c!='/'){
                    if(c=='\n'){
                        lineCount++;
                        c=fgetc(fp);
                    }else
                        c=fgetc(fp);
                }
            }
        }
        c=fgetc(fp);
    }
    return lineCount;
}
