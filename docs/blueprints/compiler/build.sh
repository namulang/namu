echo build...
flex -d flex.l
if [ $? -eq 0 ]; then
    bison bison.cpp --defines=bison.h -o bison.tab.cpp --debug
    if [ $? -eq 0 ]; then
        g++ bison.tab.cpp lex.yy.c main.cpp -o wrdcd -g -DYYDEBUG=1
    fi
fi

flex flex.l
if [ $? -eq 0 ]; then
    bison bison.cpp --defines=bison.h -o bison.tab.cpp --debug
    if [ $? -eq 0 ]; then
        g++ bison.tab.cpp lex.yy.c main.cpp -o wrdc -g -DYYDEBUG=1
        if [ $? -eq 0 ]; then
            echo done. running...
            ./wrdcd -d hello.wrd
            #./wrdc -d
            if [ $? -ne 0 ]; then
                #gdb ./wrdcd
                echo failed.
            fi
        fi

    fi
fi
