char * convert(char * s, int numRows){
    int len=strlen(s);
    if(len<=numRows || numRows==1){//if there is only one row or column,there will be an endless loop.
        return s;
    }
    char *str;
    str=(char*)malloc(len+1);
    int j=0,t=0;
    for(int k=0;k<numRows;k++)//k is row-1.
    {   
        //each row moves the number of bits per time:all = odd-number movement + even-number movement.
        if(k < numRows/2)
            t=2*(numRows-1)-2*k;//first half
        else
            t=2*k;//last half
        int i=k;
        int j_temp=j;//save the number of digits at the beginning of this line.
        while(i<len)
        {
            str[j]=s[i];
            int wei;
            if(k < numRows/2)   wei=j-j_temp+1;//first half is odd
            else                wei=j-j_temp;//last half is even
            if (k!=0 && k!=numRows-1)//exclude the first row and the last row.
            {
                if(wei%2){
                    i+=t;//even move
                }else if( wei%2==0){
                    i+=(2*(numRows-1)-t);//odd move.
                }
            }
            else
            {
                i+=t;//the first and the last rows.
            }
            j++;
        }
    }
    str[j]='\0';
    return str;
}