echo build...
flex -d wrdc.l
if [ $? -eq 0 ]; then
    bison wrdcBison.cpp --defines=wrdcBison.h -o wrdcBison.tab.cpp --debug
    if [ $? -eq 0 ]; then
        clang++ --std=c++17 wrdcBison.tab.cpp lex.yy.c main.cpp -o ../../../../bin/wrdcd -g -DYYDEBUG=1
        flex wrdc.l
        if [ $? -eq 0 ]; then
            bison wrdcBison.cpp --defines=wrdcBison.h -o wrdcBison.tab.cpp --debug
            if [ $? -eq 0 ]; then
                clang++ --std=c++17 wrdcBison.tab.cpp lex.yy.c main.cpp -o ../../../../bin/wrdc -g
                if [ $? -eq 0 ]; then
                    echo done.
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
