echo build...
flex -d wrdc.l
if [ $? -eq 0 ]; then
    bison wrdcBison.cpp --defines=wrdcBison.h -o wrdcBison.tab.cpp --debug
    if [ $? -eq 0 ]; then
        g++ wrdcBison.tab.cpp lex.yy.c main.cpp -o wrdcd -g -DYYDEBUG=1
        flex wrdc.l
        if [ $? -eq 0 ]; then
            bison wrdcBison.cpp --defines=wrdcBison.h -o wrdcBison.tab.cpp --debug
            if [ $? -eq 0 ]; then
                g++ wrdcBison.tab.cpp lex.yy.c main.cpp -o wrdc -g
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
    fi
fi

