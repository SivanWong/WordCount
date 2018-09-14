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
    //形成一个循环
    do{
        system("cls");
        printf("\n/**************欢迎使用WordCount**************/\n\n");
        printf("（格式为：wc.exe [parameter] [file_name]）\n\n");
        printf("请输入用户命令：");
        while((c=getchar())!='\n'){
            scanf("%s%s%s",str1,str2,str3);  //分组存储输入的指令
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
            printf("\n暂不支持%c命令\n",str2[1]);
        }
    }while(str2[1]=='c'||str2[1]=='w'||str2[1]=='l'||str2[1]=='a');
    getchar();
    return 0;
}


// 返回文件的字符数
int CharCount(char *filename){
    FILE * fp;
    int charCount=0;
    char c;
    //先判断文件能否打开
    if((fp=fopen(filename,"r"))==NULL){
        printf("无法打开文件\n");
    }else{
        while(!feof(fp)){
            c=fgetc(fp);  //读入文件中的字符
            if(isalnum(c)){   //判断字符是否为英文、数字字符
                charCount++;
            }
        }
        printf("\n该文件的字符数为：%d\n\n",charCount);
    }
    return charCount;
}


//返回文件的单词数
int WordCount(char *filename){
    FILE * fp;
    int wordCount=0, word=0;
    char c;
    if((fp=fopen(filename,"r"))==NULL){
        printf("无法打开文件\n");
    }else{
        c=fgetc(fp);
        while(c!=EOF){
            if(isalpha(c)) //判断字符是否为英文字符
                word=1;    //标记为一个单词的开始
            else if(c=='-'&&word==1){
                word=1;
            }else{
                if(word==1){
                    wordCount++;
                    word=0;  //一个单词结束，重置为0
                }
            }
            c=fgetc(fp);
        }
        if(c==EOF&&word==1) //为了防止文件结束符前没有除英文字符及连接符以外的字符导致没有计数
            wordCount++;
        printf("\n该文件的单词数为：%d\n\n",wordCount);
    }
    return wordCount;
}

//返回文件的行数
int LineCount(char *filename){
    FILE * fp;
    int lineCount=0, line=0;
    char c;
    if((fp=fopen(filename,"r"))==NULL){
        printf("无法打开文件\n");
    }else{
        c=fgetc(fp);   //读入文件中的字符
        while(c!=EOF){
            if(c!=' '&&c!='\t'&&c!='\v'&&c!='\r'&&c!='\n')
                line=1;   //标记一行的开始
            else if(c=='\n'){
                if(line==1){
                    lineCount++;
                    line=0;  //一行结束，重置为0
                }else
                    line=0;
            }
            c=fgetc(fp);
        }
        if(c==EOF && line==1)  //为了防止最后一行没有换行而没读到换行符导致没有计数
            lineCount++;
        printf("\n该文件的行数为：%d\n\n",lineCount);
    }
    return lineCount;
}

//返回文件更复杂的数据（空行、代码行、注释行）
int ComplexCount(char *filename){
    FILE * fp;
    int emptyLineCount, codeLineCount, commentLineCount;
    int EmptyLineCount(char *filename);
    int CodeLineCount(char *filename);
    int CommentLineCount(char *filename);
    if((fp=fopen(filename,"r"))==NULL){
        printf("无法打开文件\n");
    }else{
        emptyLineCount=EmptyLineCount(filename);
        codeLineCount=CodeLineCount(filename);
        commentLineCount=CommentLineCount(filename);
        printf("\n该文件的空行行数为：%d\n",emptyLineCount);
        printf("该文件的代码行行数为：%d\n",codeLineCount);
        printf("该文件的注释行行数为：%d\n\n",commentLineCount);
    }
    return 0;
}

//返回文件的空行行数
int EmptyLineCount(char *filename){
    FILE * fp;
    char c;
    int empty=1, lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c!=' '&&c!='t'&&c!='\v'&&c!='\r'&&c!='\n'&&c!='{'&&c!='}')
           empty=0;     //标记这不是空行
        else if(c=='\n'){
            if(empty==0)
                empty=1;   //重置为1
            else{
                lineCount++;
                empty=0;
            }
        }
        c=fgetc(fp);
    }
    if(c==EOF&&empty==1)  //为了防止最后一行没有换行而没读到换行符导致没有计数
        lineCount++;
    return lineCount;
}

//返回文件的代码行行数
int CodeLineCount(char *filename){
    FILE * fp;
    char c;
    int code=0, codeline=0, lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(isalnum(c)){
            if(code==1){  //判断是否已有一个有效字符
                codeline=1;  //标记为代码行的开始
                code=0;
            }else
                code=1;
        }else if(c=='\n'&&codeline==1){
            lineCount++;
            code=0;
            codeline=0;
        }else if(c=='/'){   //排除注释行
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
    if(c==EOF&&codeline==1)  //为了防止最后一行没有换行而没读到换行符导致没有计数
        lineCount++;
    return lineCount;
}

//返回文件的注释行行数
int CommentLineCount(char *filename){
    FILE * fp;
    char c;
    int lineCount=0;
    fp=fopen(filename,"r");
    c=fgetc(fp);
    while(c!=EOF){
        if(c=='/'){  //继续判断是否为注释行
            c=fgetc(fp);
            if(c=='/'){  //单行注释
                lineCount++;
                c=fgetc(fp);
                while(c!='\n') c=fgetc(fp);
            }else if(c=='*'){  //多行注释
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
