#include "mylibc.h"

myFILE* myfopen(const char *pathname, const char *mode){
    if(!mode){
        printf("Error: there is no mode");
        return -1;
    }
    if(!strcmp(mode,"r")&&!strcmp(mode,"r+")&&!strcmp(mode,"w")&&!strcmp(mode,"a")){
        printf("Error: Our file system does not support the above type of opening");
        return -1;
    }
    int myfd= myopen(pathname,0);
    if(myfd==-1){
        printf("Error: there is a problem to open the file");
        return -1;
    }
    myFILE *myFile=(myFILE*)malloc(sizeof(myFILE));
    //init the myFile
    myFile->fd=myfd;
    myFile->mode=mode;
    myFile->size=inodes[myfd].size;
    myFile->data= malloc(inodes[myfd].size+1);
    char open;
    if(mode=="r"){ open='r';}
    else if(mode=="r+"){ open='r+';}
    else if(mode=="w"){ open='w';}
    else{ open='a';}
    switch (open) {
        case 'r':
            for (int i = 0; i < myFile->size; i++){
                myFile->data[i] = dbs[myfd].data[i];
            }
            myFile->pointerFile=0;
            break;
        case 'r+':
            for (int i = 0; i < myFile->size; i++){
                myFile->data[i] = dbs[myfd].data[i];
            }
            myFile->pointerFile=0;
            break;
        case 'w':
            for (size_t i = 0; i <= myFile->size; i++)
            {
                myFile->data[i] = EOF;
            }
            myFile->pointerFile=0;
            break;
            // dbs[offset].next_block_num doesn't match any case constant r,r+,w
            //case 'a':
        default:
            myFile->pointerFile=inodes[myfd].size;
    }
    myclose(myfd);
    return myFile;

}
int myfclose(myFILE *stream){
    /**
     * The fclose() function closes a stream pointed to by stream.
     * This function deletes all buffers that are associated with the stream before closing it.
     * When it closes the stream, the function releases any buffers that the system reserved.
     * @return
     * If the stream is successfully closed, a zero value is returned.
        On failure, EOF is returned
     */
    if(!stream){ return 0;}
    free(stream->data);
    free(stream);
    return 1;
}
size_t myfread(void * ptr, size_t size, size_t nmemb, myFILE * stream){
    /***
     * size is the size of a single element being read. E.g. When reading a double the size would be sizeof(double) or commonly 8.
        nmemb is the max number of elements to read.
        Importantly, the return value is the number of elements read, not necessarily the number of bytes read.
        ptr is the location in memory to begin saving the data.
        stream is the FILE * pointer to use when reading, often the result of fopen().
     */
    int bytes, i;
    i = 0;
    bytes = nmemb*size+1;
    char* fileRead= (char*) malloc(bytes);
    while(i < bytes-1){
        fileRead[i]=stream->data[(stream->pointerFile++)+i];
        i++;
    }
    fileRead[bytes]=EOF;
    strcpy(ptr,fileRead);
    free(fileRead);
    return stream->pointerFile;
}
size_t myfwrite(const void * ptr, size_t size, size_t nmemb, myFILE * stream){
    /***
     *  The fwrite() function shall write, from the array pointed to by
       ptr, up to nitems elements whose size is specified by size, to
       the stream pointed to by stream.
    * size is the size of a single element being read. E.g. When reading a double the size would be sizeof(double) or commonly 8.
@parameters:
     ptr - This is a pointer to be written element of the array.
    size - the size of which is to be written for each element, in bytes.
    nmemb - This is the number of elements, the size of each element is size bytes.
    stream - This is a pointer to a FILE object, the FILE object specifies an output stream    @return
     The fwrite() function shall return the number of elements
       successfully written, which may be less than nitems if a write
       error is encountered. If size or nitems is 0, fwrite() shall
       return 0 and the state of the stream remains unchanged.
     */
    if(stream->mode=="r"){
        printf("Error: you cant write to the file withe this mode");
        return 0;
    }
    int bytes=nmemb*size*sizeof(ptr)+1,  i=0, WriteBytes=0;
    char* currentFileData= malloc(stream->size+1);
    WriteBytes= stream->data;
    //copy the current data
    strcpy(currentFileData,stream->data);
    //free the current memory of the stream for
    free(stream->data);
    //Allocate memory to the updated size
    stream->data = malloc(sizeof (currentFileData)+bytes+1);
    //adding the ptr data to the temp fileWrite
    strcpy(stream->data, currentFileData);
    for (int j = 0; j < size*nmemb; ++j) {
        stream->data[(stream->pointerFile++)+i]=((char*)ptr)[i];
        WriteBytes++;
    }
    return WriteBytes;
}
int myfseek(myFILE *stream, long offset, int whence){
    /**
     * The fseek() function sets the file position indicator for the
       stream pointed to by stream.  The new position, measured in
       bytes, is obtained by adding offset bytes to the position
       specified by whence.
     * Parameters
    stream − This is the pointer to a FILE object that identifies the stream.
    offset − This is the number of bytes to offset from whence.
    whence − This is the position from where offset is added. It is specified by one of the following constants −
     Return Value
    This function returns zero if successful, or else it returns a non-zero value.
     */
    if(offset<0){ return -1;}
    if(whence<0){return -1;}
    if(!stream){ return -1;}
    switch (whence) {
        case SEEK_SET:
            stream->pointerFile=offset;
            break;
        case SEEK_END:
            stream->pointerFile=stream->size+offset;
            break;
        case SEEK_CUR:
            stream->pointerFile=stream->pointerFile+offset;
            break;
            // whence doesn't match any case constant SEEK_SET, SEEK_END, SEEK_CUR
        default:
            stream->pointerFile=0;
    }
    return 0;

}
int myfscanf(myFILE * stream, const char * format, ...){
    int loops = (int)strlen(format);
    va_list arguments;
    va_start(arguments, format);
    int* d_scanf = va_arg(arguments, void*);
    char* c_scanf = va_arg(arguments, void*);
    float* f_scanf = va_arg(arguments, void*);
    for (int index = 0; index < loops; index++)
    {
        if(format[index] == '%'){
        switch (format[index + 1]) {
            case 'd':
                d_scanf = va_arg(arguments, void*);
                myfread(&d_scanf, sizeof(int), 1, stream);
                break;
            case 'f':
                f_scanf = va_arg(arguments, void*);
                myfread(&f_scanf, sizeof(float), 1, stream);
                break;
            case 'c':
                c_scanf = va_arg(arguments, void*);
                myfread(&c_scanf, sizeof(char), 1, stream);
                break;
                // whence doesn't match any case constant d, f, c pass
           }
        }
    }
    return index;
}
int myfprintf(myFILE * stream, const char * format, ...){
    int loops=(int)strlen(format);
    va_list arguments;
    va_start(arguments, format);
    int* d_printf = va_arg(arguments, void*);
    char* c_printf = va_arg(arguments, void*);
    float* f_printf = va_arg(arguments, void*);
    char* trash = va_arg(arguments, void*);
    for(int index = 0; index < loops; index++){
        if(format[index] == '%'){
            switch (format[index + 1]) {
                case 'd':
                    d_printf = va_arg(arguments, void*);
                    myfwrite(&d_printf, sizeof(int), 1, stream);
                    break;
                case 'f':
                    f_printf = va_arg(arguments, void*);
                    myfwrite(&f_printf, sizeof(float), 1, stream);
                    break;
                case 'c':
                    c_printf = va_arg(arguments, void*);
                    myfwrite(&c_printf, sizeof(char), 1, stream);
                    break;
                    // whence doesn't match any case constant d, f, c
                default:
                    while(format[index] != '%'){
                        trash = va_arg(arguments, void*);
                        myfwrite(&trash, sizeof(char), 1, stream);
                        index++;
                    }
            }}
    }
    return index;
}