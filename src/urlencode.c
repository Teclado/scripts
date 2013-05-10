/*
    Copyright (C) 2012 Free Software Foundation, Inc. <http://fsf.org/>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encode (char *input) {
      unsigned int i=0;
      unsigned int l=strlen(input);
      while (i<l) {
            if ( (isalnum(input[i])) || (input[i]=='-') || (input[i]=='_') || (input[i]=='.') || (input[i]=='~') ) {
                  printf("%c",input[i]);
            } else if (input[i]>=0) {
                  printf("%%%02X",input[i]);
            } else if (input[i]==-62) {
                  i++;
                  printf("%%%02X",(unsigned char)input[i]);
            } else if (input[i]==-61) {
                  i++;
                  printf("%%%02X",(unsigned char)input[i]+64);
            }
            i++;
      }
}

void decode (char *input) {
      unsigned int i=0;
      unsigned int l=strlen(input);
      unsigned char c,b;
      while (i<l) {
            if (input[i]=='%') {
                  c=0;
                  b=0;
                  if ( (input[i+1]>=97) && (input[i+1]<=102) ) {
                        c=input[i+1]-87;
                        c<<=4;
                        b++;
                  } else if ( (input[i+1]>=65) && (input[i+1]<=70) ) {
                        c=input[i+1]-55;
                        c<<=4;
                        b++;
                  } else if ( (input[i+1]>=48) && (input[i+1]<=57) ){
                        c=input[i+1]-48;
                        c<<=4;
                        b++;
                  }
                  if ( (input[i+2]>=97) && (input[i+2]<=102) ) {
                        c+=input[i+2]-87;
                        b++;
                  } else if ( (input[i+2]>=65) && (input[i+2]<=70) ) {
                        c+=input[i+2]-55;
                        b++;
                  } else if ( (input[i+2]>=48) && (input[i+2]<=57) ){
                        c+=input[i+2]-48;
                        b++;
                  }
                  if (b==2) {
                        printf("%lc",c);
                  } else {
                        printf("%%%c%c",input[i+1],input[i+2]);
                  }
                  i+=2; 
            } else {
                  printf("%c",input[i]);
            }
            i++;
      }
}

int main (int narg, char *argv[]) {

      char *lo = setlocale(LC_ALL,"");

      unsigned int i=1;
      while (i<narg) {
            if (strcmp(argv[i],"-e")==0) {
                  i++;
                  encode(argv[i]);
            } else if (strcmp(argv[i],"-d")==0) {
                  i++;
                  decode(argv[i]);
            } else if (strcmp(argv[i],"-l")==0) {
                  i++;
                  lo = setlocale(LC_ALL,argv[i]);
            } else if (strcmp(argv[i],"-h")==0) {
                  printf("\r%s usage:\n",argv[0]);
                  printf("\t%s [-h] [-l locale] [-e|-d] message\n\n",argv[0]);
                  printf("\t-e message\n");
                  printf("\t\tEncode message according to the locale set by -l.\n\n");
                  printf("\t-d message\n");
                  printf("\t\tDecode message according to the locale set by -l.\n\n");
                  printf("\t-l locale\n");
                  printf("\t\tSet the locale to use. If no -l option is specified\n\t\tthe system's one will be used. This can be used at\n\t\tany point of the input line and will affect all\n\t\tsubsecuent inputs.\n\n");
                  printf("\t-h\n");
                  printf("\t\tPrint this help and exit.\n\n");
                  printf("\tIf multiple -e/-d options are facilited the output will\n\tconcatenate the results. If no -e/-d option are used the\n\tusual behaviour is to encode the string whatever was it.\n\n");
                  printf("\tCurrent locale is %s.\n",lo);
                  return 0;
            } else {
                  encode(argv[i]);
            }
            i++;
      }

      return 0;
}

