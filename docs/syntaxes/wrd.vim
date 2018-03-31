" Vim syntax file
" Language:    	World 
" Maintainer:   kniz <kniz@kniz.net>
" URL:			kniz.net
" Last Change:  2018 Mar 30

" quit when a syntax file was already loaded
if exists("b:current_syntax")
  finish
endif

" Defines
syn keyword defKeyword		class extend inherit if for while true false
syn keyword defPretype		int float void result string char null
syn match defIdentifier		"[_a-z0-9]\+"
syn match defClass			"[A-Z][a-zA-Z0-9]\+"
syn match defMethod			/[_a-zA-Z0-9]\+(/he=e-1
syn match defOperator		"!=\|:=:\|=<\|>=\|=\|+\|\*\|/\|<->\|->\|<-\|:-\|!-\|-\|<\|>"
syn match defBrace			"(\|)\|\[\|\]\|{\|}"
syn match defComment      	"//[^\n]*"
syn region defString		start=+"+ end=+"+

" Colors
highlight clrKeyword 		ctermfg=Red 	guifg=#EA2E49
highlight clrPretype		ctermfg=Red 	guifg=#EA2E49
highlight clrClass			ctermfg=Yellow 	guifg=#E3CDA4
highlight clrIdentifier		ctermfg=Cyan 	guifg=#77C4D3
highlight clrString			ctermfg=Green 	guifg=#E6E7A7
hi clrOperator				ctermfg=Gray 	guifg=#8C95A1
"hi clrBrace				ctermfg=LightBlue
hi clrComment				ctermfg=Gray	guifg=#7E827A
hi clrMethod				ctermfg=DarkRed	guifg=#D9FF99

" Linkage
hi def link defKeyword		clrKeyword
hi def link defPretype		clrPretype
hi def link defClass		clrClass
hi def link defOperator		clrOperator
hi def link defBrace		clrOperator
hi def link defString		clrString
hi def link defIdentifier	clrIdentifier
hi def link defComment		clrComment
hi def link defMethod		clrMethod

let b:current_syntax = "wrd"

