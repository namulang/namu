var store = [{
        "title": "intro",
        "excerpt":"안녕하세요!   시작하면서   kniz 라고 합니다. Namu 언어(이하 namulang)를 배우기로 결심하셨군요.   프로그래밍 언어를 배우는 것은 영어나 스페인어를 배우는 것과 공통점이 있습니다. 많은 지식과 더불어 연습을 필요로 점에서요.   되새겨보면, 어떻게 하면 간단하면서도 가지고 놀기 좋은 문법을 만들 수 있을까 많은 고민을 했습니다만, 그럼에도 불구하고 이 언어를 배우는 것은 절대 쉬운 여행은 아닐겁니다.   가벼운 마음으로 이 페이지를 여셨든, 혹은 심호흡을 깊게 하셨든 간에 무엇보다 시간을 내서 배워보겠다는 결심을 해주신 것에 깊은 감사를 드립니다.   즉, 이 곳은 그러한 namulang을 사용하기 위한 출발점이라고 할 수 있습니다. 게다가 모든 여정은 한글로 작성되었구요. 만세!   아, 어디서부터 시작해야 할지 난감하실텐데요. 밑에 나오는 목록에서 위에서부터 아래로 문서를 차근차근 읽으면 됩니다. 쉽죠? 그리고. 이렇게 배운 것들은 바로 써먹어 보고 싶다면 상단의 play 쪽에서 시도해볼 수도 있구요.   음, 제가 얼른 이 여행의 끝까지 한번 굽어보고 왔는데요. 짧다면 짧지만, 길다면 긴 여행이 될 것 같아요. 제가 한동안 동행하겠네요. 그러니 그 동안은 서로 딱딱하게 지내지는 말죠.   뭐든지 시작이란 단어는 항상 설레임을 주네요. 그 설레임을 안고, 같이 떠나보시죠.   부디 끝까지 함께 하시기를.  ","categories": [],
        "tags": [],
        "url": "/guide/",
        "teaser": null
      },{
        "title": "quick start",
        "excerpt":"미리 모든 내용을 훑어보죠.   시작하기전에   어떤 분은 프로그래밍 언어를 많이 접해봐서, 아래 내용만으로도 어떠한 언어고 어떻게 사용하면 되는지 깨닫는 분도 있을 거예요.  그런 분들은 필요한 항목만 추가로 열람하고 자유롭게 이곳을 떠나셔도 좋습니다.   혹, 난 그게 아니구나 싶으시다면, 아래 내용들이 좀 혼란스러울 수 있어요.  하지만 어짜피 다시 자세하게 다룰 예정이니까 좀 이해가 안가셔도 괜찮거든요.  빠르게 훑어보고 지나가셔도 괜찮아요.   시작은 hello world 죠?   main() void     print(\"Hello world!\")   변수와 표현식   정의시, type은 항상 뒤에 옵니다.   str1 := \"message\" // 변수의 정의 str1 = \"wow\"  bool1 := false flt1 := 3.5 + 3 char1 := 'c' int1 := 15  // casts int as 64bit float, after that assign it to variable 'toInt' toInt := int1 as flt64   Indentation 레벨에 의한 Scope 범위   항상 Indentation 레벨에 의해서 scope를 표현합니다.   val := 0 if val == 0     if val &gt; 0         print('ok') else     print('no')   ’:’를 사용하면 indent 없이 block문을 작성할 수 있구요.   // ':' only allow to follow a single statement. if val == 0: print('this and then,')     print('this too') // err  // below codes are same to the above. if val == 0: if val &gt; 0: print('ok') else: print('no') // 'else' has no indentation level. /* if above 'else' statement has 1 level indentation like below,      if val == 0: if val &gt; 0: print('ok')         else: print('no')      then it's like,      if val == 0         if val &gt; 0             print('ok')         else             print('no') */   closure도 동일합니다.   closure(n int) int = null  if val &gt; 0     callClosure(c closure, n int) void         c(n)      callClosure((n int) int         return n + 5     , 22) // watch the comma. it's align to the indentation of 'callClosure' function call.           // which means that it's belongs to the call as one of argument.           // if the comma has been attached to the end of 'return' statment inside function,           // it has totally different meaning.      /* callClosure((n int) int         return n + 5, 22)     ',' is belongs to the line which has 2 indentation level. so it exists as one of term of     'return' statement.     now 'callClosure' function is returning two integer, n+5 and 22, and is not valid syntax     in namulang. */      callClosure((n): switch n: 22, 23: doSomething(), 23) // ok     // in above statement, comma was also used to represent the case statement, but it's not     // ambigious because every case statement has at least one statement.      callClosure((n): switch n: 22, 23: doSomething()     , 23) // err. newline should not exist when you put ':' to represent a block statement.   흐름 제어  msg := \"hello\" for ch in msg     c.print(\"ch=$ch \") // this'll shows like 'ch=h ch=e ch=l ch=l ch=o'  n := 0 for ++n &lt; 3     if sum in 1..0 // allow reversed range.         sum += n     elif sum == 2 // elif is same to 'else if'         sum -= n   컨테이너   intArr := {1, 2, 3} floatArr := {1.5, 2.5, 3.5}  seq := 2..4 seq.len == 3 // true for n in seq     c.print(intArr[n])  pair1 := intArr[2];\"banana\" // ';' represents a pair. and a pair contains 'key' and 'val'. pair1.key == 3.5 // false pair1.val = \"money?\"  map := {pair1, 2.5;\"apple\"} // map as float[str]  aka sys.cons -&gt; c.print(\"how many apple do you have = $map['apple']\") // \"how many apple do you have = 2.0\"   함수     &lt;function-name&gt; '(' &lt;arg&gt; ',' &lt;arg&gt;... ')' &lt;return-type&gt;        &lt;stmt&gt;+      정의시, 역시 type은 항상 뒤에 옵니다.   함수의 반환형에는 expr이 올 수 없습니다. 타입만 올 수 있습니다.   반드시 함수의 body를 정의해야 합니다.   getLen(b int...) int // '...' means varidic argument     sum := 0     for n in b         sum++     return sum  getLen(b int) // return type is deduced to 'int'     sum := 0     return sum  (b int) // ok. but never got called. because it has no name.     sum := 0     return sum      fun := () // == declare a closure refering &lt;nameless function&gt;() str.     return \"\" fun()  setClickListener((v): v.onClick()) // if a func was nested, it works like a closure.  // getLen(b int) // err. this is ambigious. if the body of func was missing, it should be regarded to a function call.  foo(useless int...) int = null // 'null' declares that this is abstract method def. likeFptr := foo // foo can be used as a type. likeFptr() // foo is abstract. Exception occurs.  likeFptr = getLen // ok to assign. lifeFptr() == 0 // true   객체정의   aka sys.cons -&gt; c  def base // base is incomplete origin object     _realAge := 0 // \"_\" means protected      age int // this property don't have a value.         get(): realAge + 1         set(new int): realAge = new // it refers the parameter of this method which has a single parameter.      age2 := 0 // this property has value.         get(old int): return old + 1 // getter should accepts 1 argument holding the value.         set(new int) int: return new      age3 := 0 // convenient way.         get: return it + 1         set: return it      me(newAge int)         realAge = newAge         c.out(\"constructor(int)\")      me(): c.out(\"constructor()\")      say() str? // returning value can be assigned to null.         c.out(\"age=$age\")         return null  def derive(1) from base // derive is complete origin object      me(new int) // ctor does nothing but calls super()         super(new)      // overrided     say() str?          c.out(\"derive.say!\")  def derive2(2) from base(22) // you can call constructor of superclass.     // this 'derive2' is like a static variable of other languages.  b1 := base(1) // b was created from \"base\" object. b1.say() // \"age=2\" derive.say() derive.say() // now, \"age=2\"  // derive.realAge // can't access private member at outside.  msg1 := \"hello\" // string is also a object. msg2 := \"hel\" + \"lo\" msg1 == msg2 // true msg1 === msg2 // however, they aren't same object.   표현식기반   max := if isGood := false // max as int     c.out(\"never reach here.\")     c.out(\"and returns the last expr to outside of block\")     -1  else: c.out(\"or use \\\"ret\\\" keyword\"): ret 10  if isGood: return; // never reach here  val := for n in 0..max // \"for\" returns last expr while it loops.     n val == 10 // true   프로퍼티  def myObj     age := 22 // age as int. it has value 22. but is also property.         get             sys.cons.out(\"this will return $it\")             return it   def myObj2     age := 22         set(new int) int: cout(\"age.$new\")         _get // get is normally returning value of age but isn't accessible from outside.         // same as, '_get(old int) int: return old'  def app     main() void         with myObj             age // == 22             age = 5             age // == 5          myObj2.age = 10         if myObj2.age == 10 // compile err. it's protected.   closure   def app     func() int = null // abstract method.     // when you declare a func, the func can be also used as a type.      foo() func // returns a function matching the signature of 'func' function.          def cnt() from 0 // origin object can be shared and exist as only one instance during the process.          arr := int[]         for (n := 1) &lt; ++cnt             arr.add(n)          getLenFrom() int // a nested method like a closure.             arr.len // so, arr can be captured.                     // all of expr always returns last expr to outside.         ret getLenFrom // the capturing of arr variable occurs at here. (when assigning value to a closure)      main() void         foo()() // == 1         foo()() // == 2   exceptions   def app     safeNavigation() void         activity?.appContext?.res?.getString(1) // safe navigation      exceptionHandling() int on nullErr, ioErr // specifying that returns err with value.         try Resources res = getActivity().getAppContext().getResources()         on nullErr: return it // throw.         on ioErr: return -1 on it          return err(\"unknown\")      foo(val int) int         return val      main() void         safeNavigation()          // try is available when calls method specified errs with \"on\" keyword.         try val := foo(exceptionHandling())         on err: ret handling()          if val == -1             try val = foo(exceptionHandling())             on err:                 sys.cons.out(\"you will see this sentence.\")                 return   결과: you will see this sentence   all preserved keywords   syntax   def from with if elif else ret return continue switch import pack aka as try on in for   primitive types   int int8 int16 int32 int64 flt flt32 flt64 str bool char void err obj null   predeclared objects   me it null super   operators   . _ + - / * % += := == === -= /= = ^ %= ! ^ &amp; | !! ^^ &amp;&amp; || [] …  () ++ ** – // / */ : =&gt; -&gt; ,  ","categories": [],
        "tags": [],
        "url": "/guide/quick-start",
        "teaser": null
      },{
        "title": "Exclude Post from Search Index",
        "excerpt":"This post should not appear in the search index because it has the following YAML Front Matter:   search: false   Note: search: false only works to exclude posts when using Lunr as a search provider.   To exclude files when using Algolia as a search provider add an array to algolia.files_to_exclude in your _config.yml. For more configuration options be sure to check their full documentation.   algolia:   # Exclude more files from indexing   files_to_exclude:     - index.html     - index.md     - excluded-file.html     - _posts/2017-11-28-post-exclude-search.md     - subdirectory/*.html  ","categories": ["Jekyll"],
        "tags": [],
        "url": "/jekyll/post-exclude-search/",
        "teaser": null
      },{
    "title": null,
    "excerpt":"소개  ","url": "http://localhost:4000/about/"
  },{
    "title": null,
    "excerpt":"                                                                              verbose mode                ","url": "http://localhost:4000/play/"
  },{
    "title": null,
    "excerpt":"","url": "http://localhost:4000/"
  },{
    "title": "intro",
    "excerpt":"안녕하세요!   시작하면서   kniz 라고 합니다. Namu 언어(이하 namulang)를 배우기로 결심하셨군요.   프로그래밍 언어를 배우는 것은 영어나 스페인어를 배우는 것과 공통점이 있습니다. 많은 지식과 더불어 연습을 필요로 점에서요.   되새겨보면, 어떻게 하면 간단하면서도 가지고 놀기 좋은 문법을 만들 수 있을까 많은 고민을 했습니다만, 그럼에도 불구하고 이 언어를 배우는 것은 절대 쉬운 여행은 아닐겁니다.   가벼운 마음으로 이 페이지를 여셨든, 혹은 심호흡을 깊게 하셨든 간에 무엇보다 시간을 내서 배워보겠다는 결심을 해주신 것에 깊은 감사를 드립니다.   즉, 이 곳은 그러한 namulang을 사용하기 위한 출발점이라고 할 수 있습니다. 게다가 모든 여정은 한글로 작성되었구요. 만세!   아, 어디서부터 시작해야 할지 난감하실텐데요. 밑에 나오는 목록에서 위에서부터 아래로 문서를 차근차근 읽으면 됩니다. 쉽죠? 그리고. 이렇게 배운 것들은 바로 써먹어 보고 싶다면 상단의 play 쪽에서 시도해볼 수도 있구요.   음, 제가 얼른 이 여행의 끝까지 한번 굽어보고 왔는데요. 짧다면 짧지만, 길다면 긴 여행이 될 것 같아요. 제가 한동안 동행하겠네요. 그러니 그 동안은 서로 딱딱하게 지내지는 말죠.   뭐든지 시작이란 단어는 항상 설레임을 주네요. 그 설레임을 안고, 같이 떠나보시죠.   부디 끝까지 함께 하시기를.  ","url": "http://localhost:4000/guide/"
  },{
    "title": null,
    "excerpt":"var idx = lunr(function () {   this.field('title')   this.field('excerpt')   this.field('categories')   this.field('tags')   this.ref('id')    this.pipeline.remove(lunr.trimmer)    for (var item in store) {     this.add({       title: store[item].title,       excerpt: store[item].excerpt,       categories: store[item].categories,       tags: store[item].tags,       id: item     })   } });  $(document).ready(function() {   $('input#search').on('keyup', function () {     var resultdiv = $('#results');     var query = $(this).val().toLowerCase();     var result =       idx.query(function (q) {         query.split(lunr.tokenizer.separator).forEach(function (term) {           q.term(term, { boost: 100 })           if(query.lastIndexOf(\" \") != query.length-1){             q.term(term, {  usePipeline: false, wildcard: lunr.Query.wildcard.TRAILING, boost: 10 })           }           if (term != \"\"){             q.term(term, {  usePipeline: false, editDistance: 1, boost: 1 })           }         })       });     resultdiv.empty();     resultdiv.prepend(''+result.length+' Result(s) found ');     for (var item in result) {       var ref = result[item].ref;       if(store[ref].teaser){         var searchitem =           ''+             ''+               ''+                 ''+store[ref].title+''+               ' '+               ''+                 ''+               ''+               ''+store[ref].excerpt.split(\" \").splice(0,20).join(\" \")+'... '+             ''+           '';       }       else{     \t  var searchitem =           ''+             ''+               ''+                 ''+store[ref].title+''+               ' '+               ''+store[ref].excerpt.split(\" \").splice(0,20).join(\" \")+'... '+             ''+           '';       }       resultdiv.append(searchitem);     }   }); }); ","url": "http://localhost:4000/assets/js/lunr/lunr-en.js"
  },{
    "title": null,
    "excerpt":"step1list = new Array(); step1list[\"ΦΑΓΙΑ\"] = \"ΦΑ\"; step1list[\"ΦΑΓΙΟΥ\"] = \"ΦΑ\"; step1list[\"ΦΑΓΙΩΝ\"] = \"ΦΑ\"; step1list[\"ΣΚΑΓΙΑ\"] = \"ΣΚΑ\"; step1list[\"ΣΚΑΓΙΟΥ\"] = \"ΣΚΑ\"; step1list[\"ΣΚΑΓΙΩΝ\"] = \"ΣΚΑ\"; step1list[\"ΟΛΟΓΙΟΥ\"] = \"ΟΛΟ\"; step1list[\"ΟΛΟΓΙΑ\"] = \"ΟΛΟ\"; step1list[\"ΟΛΟΓΙΩΝ\"] = \"ΟΛΟ\"; step1list[\"ΣΟΓΙΟΥ\"] = \"ΣΟ\"; step1list[\"ΣΟΓΙΑ\"] = \"ΣΟ\"; step1list[\"ΣΟΓΙΩΝ\"] = \"ΣΟ\"; step1list[\"ΤΑΤΟΓΙΑ\"] = \"ΤΑΤΟ\"; step1list[\"ΤΑΤΟΓΙΟΥ\"] = \"ΤΑΤΟ\"; step1list[\"ΤΑΤΟΓΙΩΝ\"] = \"ΤΑΤΟ\"; step1list[\"ΚΡΕΑΣ\"] = \"ΚΡΕ\"; step1list[\"ΚΡΕΑΤΟΣ\"] = \"ΚΡΕ\"; step1list[\"ΚΡΕΑΤΑ\"] = \"ΚΡΕ\"; step1list[\"ΚΡΕΑΤΩΝ\"] = \"ΚΡΕ\"; step1list[\"ΠΕΡΑΣ\"] = \"ΠΕΡ\"; step1list[\"ΠΕΡΑΤΟΣ\"] = \"ΠΕΡ\"; step1list[\"ΠΕΡΑΤΑ\"] = \"ΠΕΡ\"; step1list[\"ΠΕΡΑΤΩΝ\"] = \"ΠΕΡ\"; step1list[\"ΤΕΡΑΣ\"] = \"ΤΕΡ\"; step1list[\"ΤΕΡΑΤΟΣ\"] = \"ΤΕΡ\"; step1list[\"ΤΕΡΑΤΑ\"] = \"ΤΕΡ\"; step1list[\"ΤΕΡΑΤΩΝ\"] = \"ΤΕΡ\"; step1list[\"ΦΩΣ\"] = \"ΦΩ\"; step1list[\"ΦΩΤΟΣ\"] = \"ΦΩ\"; step1list[\"ΦΩΤΑ\"] = \"ΦΩ\"; step1list[\"ΦΩΤΩΝ\"] = \"ΦΩ\"; step1list[\"ΚΑΘΕΣΤΩΣ\"] = \"ΚΑΘΕΣΤ\"; step1list[\"ΚΑΘΕΣΤΩΤΟΣ\"] = \"ΚΑΘΕΣΤ\"; step1list[\"ΚΑΘΕΣΤΩΤΑ\"] = \"ΚΑΘΕΣΤ\"; step1list[\"ΚΑΘΕΣΤΩΤΩΝ\"] = \"ΚΑΘΕΣΤ\"; step1list[\"ΓΕΓΟΝΟΣ\"] = \"ΓΕΓΟΝ\"; step1list[\"ΓΕΓΟΝΟΤΟΣ\"] = \"ΓΕΓΟΝ\"; step1list[\"ΓΕΓΟΝΟΤΑ\"] = \"ΓΕΓΟΝ\"; step1list[\"ΓΕΓΟΝΟΤΩΝ\"] = \"ΓΕΓΟΝ\";  v = \"[ΑΕΗΙΟΥΩ]\"; v2 = \"[ΑΕΗΙΟΩ]\"  function stemWord(w) {   var stem;   var suffix;   var firstch;   var origword = w;   test1 = new Boolean(true);    if(w.length '+result.length+' Result(s) found ');     for (var item in result) {       var ref = result[item].ref;       if(store[ref].teaser){         var searchitem =           ''+             ''+               ''+                 ''+store[ref].title+''+               ' '+               ''+                 ''+               ''+               ''+store[ref].excerpt.split(\" \").splice(0,20).join(\" \")+'... '+             ''+           '';       }       else{     \t  var searchitem =           ''+             ''+               ''+                 ''+store[ref].title+''+               ' '+               ''+store[ref].excerpt.split(\" \").splice(0,20).join(\" \")+'... '+             ''+           '';       }       resultdiv.append(searchitem);     }   }); }); ","url": "http://localhost:4000/assets/js/lunr/lunr-gr.js"
  },{
    "title": null,
    "excerpt":"var store = [   {%- for c in site.collections -%}     {%- if forloop.last -%}       {%- assign l = true -%}     {%- endif -%}     {%- assign docs = c.docs | where_exp:'doc','doc.search != false' -%}     {%- for doc in docs -%}       {%- if doc.header.teaser -%}         {%- capture teaser -%}{{ doc.header.teaser }}{%- endcapture -%}       {%- else -%}         {%- assign teaser = site.teaser -%}       {%- endif -%}       {         \"title\": {{ doc.title | jsonify }},         \"excerpt\":           {%- if site.search_full_content == true -%}             {{ doc.content | newline_to_br |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \"|             strip_html | strip_newlines | jsonify }},           {%- else -%}             {{ doc.content | newline_to_br |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \" |               replace:\" \", \" \"|             strip_html | strip_newlines | truncatewords: 50 | jsonify }},           {%- endif -%}         \"categories\": {{ doc.categories | jsonify }},         \"tags\": {{ doc.tags | jsonify }},         \"url\": {{ doc.url | relative_url | jsonify }},         \"teaser\": {{ teaser | relative_url | jsonify }}       }{%- unless forloop.last and l -%},{%- endunless -%}     {%- endfor -%}   {%- endfor -%}{%- if site.lunr.search_within_pages -%},   {%- assign pages = site.pages | where_exp:'doc','doc.search != false' -%}   {%- for doc in pages -%}     {%- if forloop.last -%}       {%- assign l = true -%}     {%- endif -%}   {     \"title\": {{ doc.title | jsonify }},     \"excerpt\":         {%- if site.search_full_content == true -%}           {{ doc.content | newline_to_br |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \"|           strip_html | strip_newlines | jsonify }},         {%- else -%}           {{ doc.content | newline_to_br |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \" |             replace:\" \", \" \"|           strip_html | strip_newlines | truncatewords: 50 | jsonify }},         {%- endif -%}       \"url\": {{ doc.url | absolute_url | jsonify }}   }{%- unless forloop.last and l -%},{%- endunless -%}   {%- endfor -%} {%- endif -%}] ","url": "http://localhost:4000/assets/js/lunr/lunr-store.js"
  },{
    "title": null,
    "excerpt":"","url": "http://localhost:4000/posts/"
  },{
    "title": "quick start",
    "excerpt":"미리 모든 내용을 훑어보죠.  ## 시작하기전에  어떤 분은 프로그래밍 언어를 많이 접해봐서, 아래 내용만으로도 어떠한 언어고 어떻게 사용하면 되는지 깨닫는 분도 있을 거예요. 그런 분들은 필요한 항목만 추가로 열람하고 자유롭게 이곳을 떠나셔도 좋습니다.  혹, 난 그게 아니구나 싶으시다면, 아래 내용들이 좀 혼란스러울 수 있어요. 하지만 어짜피 다시 자세하게 다룰 예정이니까 좀 이해가 안가셔도 괜찮거든요. 빠르게 훑어보고 지나가셔도 괜찮아요.   ## 시작은 hello world 죠?   ```go main() void     print(\"Hello world!\") ```   ## 변수와 표현식  정의시, type은 항상 뒤에 옵니다.  ```go str1 := \"message\" // 변수의 정의 str1 = \"wow\"  bool1 := false flt1 := 3.5 + 3 char1 := 'c' int1 := 15  // casts int as 64bit float, after that assign it to variable 'toInt' toInt := int1 as flt64 ```  ## Indentation 레벨에 의한 Scope 범위  항상 Indentation 레벨에 의해서 scope를 표현합니다.  ```go val := 0 if val == 0     if val > 0         print('ok') else     print('no') ```  ':'를 사용하면 indent 없이 block문을 작성할 수 있구요.  ```go // ':' only allow to follow a single statement. if val == 0: print('this and then,')     print('this too') // err  // below codes are same to the above. if val == 0: if val > 0: print('ok') else: print('no') // 'else' has no indentation level. /* if above 'else' statement has 1 level indentation like below,      if val == 0: if val > 0: print('ok')         else: print('no')      then it's like,      if val == 0         if val > 0             print('ok')         else             print('no') */ ```  closure도 동일합니다.  ```go closure(n int) int = null  if val > 0     callClosure(c closure, n int) void         c(n)      callClosure((n int) int         return n + 5     , 22) // watch the comma. it's align to the indentation of 'callClosure' function call.           // which means that it's belongs to the call as one of argument.           // if the comma has been attached to the end of 'return' statment inside function,           // it has totally different meaning.      /* callClosure((n int) int         return n + 5, 22)     ',' is belongs to the line which has 2 indentation level. so it exists as one of term of     'return' statement.     now 'callClosure' function is returning two integer, n+5 and 22, and is not valid syntax     in namulang. */      callClosure((n): switch n: 22, 23: doSomething(), 23) // ok     // in above statement, comma was also used to represent the case statement, but it's not     // ambigious because every case statement has at least one statement.      callClosure((n): switch n: 22, 23: doSomething()     , 23) // err. newline should not exist when you put ':' to represent a block statement. ```   ## 흐름 제어 ```go msg := \"hello\" for ch in msg     c.print(\"ch=$ch \") // this'll shows like 'ch=h ch=e ch=l ch=l ch=o'  n := 0 for ++n  c.print(\"how many apple do you have = $map['apple']\") // \"how many apple do you have = 2.0\" ```   ## 함수 ```     '('  ',' ... ')'         + ```  * 정의시, 역시 type은 항상 뒤에 옵니다. * 함수의 반환형에는 expr이 올 수 없습니다. 타입만 올 수 있습니다. * 반드시 함수의 body를 정의해야 합니다.  ```go getLen(b int...) int // '...' means varidic argument     sum := 0     for n in b         sum++     return sum  getLen(b int) // return type is deduced to 'int'     sum := 0     return sum  (b int) // ok. but never got called. because it has no name.     sum := 0     return sum      fun := () // == declare a closure refering () str.     return \"\" fun()  setClickListener((v): v.onClick()) // if a func was nested, it works like a closure.  // getLen(b int) // err. this is ambigious. if the body of func was missing, it should be regarded to a function call.  foo(useless int...) int = null // 'null' declares that this is abstract method def. likeFptr := foo // foo can be used as a type. likeFptr() // foo is abstract. Exception occurs.  likeFptr = getLen // ok to assign. lifeFptr() == 0 // true ```   ## 객체정의  ```go aka sys.cons -> c  def base // base is incomplete origin object     _realAge := 0 // \"_\" means protected      age int // this property don't have a value.         get(): realAge + 1         set(new int): realAge = new // it refers the parameter of this method which has a single parameter.      age2 := 0 // this property has value.         get(old int): return old + 1 // getter should accepts 1 argument holding the value.         set(new int) int: return new      age3 := 0 // convenient way.         get: return it + 1         set: return it      me(newAge int)         realAge = newAge         c.out(\"constructor(int)\")      me(): c.out(\"constructor()\")      say() str? // returning value can be assigned to null.         c.out(\"age=$age\")         return null  def derive(1) from base // derive is complete origin object      me(new int) // ctor does nothing but calls super()         super(new)      // overrided     say() str?          c.out(\"derive.say!\")  def derive2(2) from base(22) // you can call constructor of superclass.     // this 'derive2' is like a static variable of other languages.  b1 := base(1) // b was created from \"base\" object. b1.say() // \"age=2\" derive.say() derive.say() // now, \"age=2\"  // derive.realAge // can't access private member at outside.  msg1 := \"hello\" // string is also a object. msg2 := \"hel\" + \"lo\" msg1 == msg2 // true msg1 === msg2 // however, they aren't same object. ```  ## 표현식기반  ```go max := if isGood := false // max as int     c.out(\"never reach here.\")     c.out(\"and returns the last expr to outside of block\")     -1  else: c.out(\"or use \\\"ret\\\" keyword\"): ret 10  if isGood: return; // never reach here  val := for n in 0..max // \"for\" returns last expr while it loops.     n val == 10 // true ```   ## 프로퍼티 ```go def myObj     age := 22 // age as int. it has value 22. but is also property.         get             sys.cons.out(\"this will return $it\")             return it   def myObj2     age := 22         set(new int) int: cout(\"age.$new\")         _get // get is normally returning value of age but isn't accessible from outside.         // same as, '_get(old int) int: return old'  def app     main() void         with myObj             age // == 22             age = 5             age // == 5          myObj2.age = 10         if myObj2.age == 10 // compile err. it's protected. ```  ## closure  ```go def app     func() int = null // abstract method.     // when you declare a func, the func can be also used as a type.      foo() func // returns a function matching the signature of 'func' function.          def cnt() from 0 // origin object can be shared and exist as only one instance during the process.          arr := int[]         for (n := 1)  -> , ","url": "http://localhost:4000/guide/quick-start"
  },{
    "title": null,
    "excerpt":"@import \"jekyll-theme-primer\"; ","url": "http://localhost:4000/assets/css/style.css"
  },{
    "title": null,
    "excerpt":"{}","url": "http://localhost:4000/redirects.json"
  },{
    "title": null,
    "excerpt":" {% if page.xsl %} {% endif %} {% assign collections = site.collections | where_exp:'collection','collection.output != false' %}{% for collection in collections %}{% assign docs = collection.docs | where_exp:'doc','doc.sitemap != false' %}{% for doc in docs %} {{ doc.url | replace:'/index.html','/' | absolute_url | xml_escape }} {% if doc.last_modified_at or doc.date %}{{ doc.last_modified_at | default: doc.date | date_to_xmlschema }} {% endif %} {% endfor %}{% endfor %}{% assign pages = site.html_pages | where_exp:'doc','doc.sitemap != false' | where_exp:'doc','doc.url != \"/404.html\"' %}{% for page in pages %} {{ page.url | replace:'/index.html','/' | absolute_url | xml_escape }} {% if page.last_modified_at %}{{ page.last_modified_at | date_to_xmlschema }} {% endif %} {% endfor %}{% assign static_files = page.static_files | where_exp:'page','page.sitemap != false' | where_exp:'page','page.name != \"404.html\"' %}{% for file in static_files %} {{ file.path | replace:'/index.html','/' | absolute_url | xml_escape }} {{ file.modified_time | date_to_xmlschema }}  {% endfor %} ","url": "http://localhost:4000/sitemap.xml"
  },{
    "title": null,
    "excerpt":"Sitemap: {{ \"sitemap.xml\" | absolute_url }} ","url": "http://localhost:4000/robots.txt"
  },{
    "title": null,
    "excerpt":"{% if page.xsl %}{% endif %}Jekyll{{ site.time | date_to_xmlschema }}{{ page.url | absolute_url | xml_escape }}{% assign title = site.title | default: site.name %}{% if page.collection != \"posts\" %}{% assign collection = page.collection | capitalize %}{% assign title = title | append: \" | \" | append: collection %}{% endif %}{% if page.category %}{% assign category = page.category | capitalize %}{% assign title = title | append: \" | \" | append: category %}{% endif %}{% if title %}{{ title | smartify | xml_escape }}{% endif %}{% if site.description %}{{ site.description | xml_escape }}{% endif %}{% if site.author %}{{ site.author.name | default: site.author | xml_escape }}{% if site.author.email %}{{ site.author.email | xml_escape }}{% endif %}{% if site.author.uri %}{{ site.author.uri | xml_escape }}{% endif %}{% endif %}{% if page.tags %}{% assign posts = site.tags[page.tags] %}{% else %}{% assign posts = site[page.collection] %}{% endif %}{% if page.category %}{% assign posts = posts | where: \"category\", page.category %}{% endif %}{% unless site.show_drafts %}{% assign posts = posts | where_exp: \"post\", \"post.draft != true\" %}{% endunless %}{% assign posts = posts | sort: \"date\" | reverse %}{% assign posts_limit = site.feed.posts_limit | default: 10 %}{% for post in posts limit: posts_limit %}{% assign post_title = post.title | smartify | strip_html | normalize_whitespace | xml_escape %}{{ post_title }}{{ post.date | date_to_xmlschema }}{{ post.last_modified_at | default: post.date | date_to_xmlschema }}{{ post.id | absolute_url | xml_escape }}{% assign excerpt_only = post.feed.excerpt_only | default: site.feed.excerpt_only %}{% unless excerpt_only %}{{ post.content | strip | xml_escape }}{% endunless %}{% assign post_author = post.author | default: post.authors[0] | default: site.author %}{% assign post_author = site.data.authors[post_author] | default: post_author %}{% assign post_author_email = post_author.email | default: nil %}{% assign post_author_uri = post_author.uri | default: nil %}{% assign post_author_name = post_author.name | default: post_author %}{{ post_author_name | default: \"\" | xml_escape }}{% if post_author_email %}{{ post_author_email | xml_escape }}{% endif %}{% if post_author_uri %}{{ post_author_uri | xml_escape }}{% endif %}{% if post.category %}{% elsif post.categories %}{% for category in post.categories %}{% endfor %}{% endif %}{% for tag in post.tags %}{% endfor %}{% if post.excerpt and post.excerpt != empty %}{{ post.excerpt | strip_html | normalize_whitespace | xml_escape }}{% endif %}{% assign post_image = post.image.path | default: post.image %}{% if post_image %}{% unless post_image contains \"://\" %}{% assign post_image = post_image | absolute_url %}{% endunless %}{% endif %}{% endfor %}","url": "http://localhost:4000/feed.xml"
  }]
