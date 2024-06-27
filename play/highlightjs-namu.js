/*
Language: namu
Description: Namu is strong-typed OOP script language.
Website: https://namu.codes
Category: common
*/

// this codes is super simple:
// may need to refactor and develop more.
(() => {
    var lang = (() => {
      const regex = hljs.regex;
      const ID = hljs.IDENT_RE;
      const ACCESSIBLE_ID = `[_\\+]*${ID}`;
      const SPACES = /[\t \f]+/;
      const SPACIBLE = /\s*/;

      const RESERVED_WORDS = [
        'def', 'as', 'is', 'ctor',
        'on', 'in', 'next', 'else',
        'for', 'if', 'ret', 'while',
        'with', 'pack', 'break', 'get',
        'set', 'end',
      ];

      const BUILT_INS = [
        'print', 'input',
      ];

      const LITERALS = [
        'true', 'false', 'nul',
      ];

      const TYPES = [
        'void', 'err', 'int', 'super',
        'byte', 'flt', 'str', 'char',
        'me', 'it',
      ];

      const KEYWORDS = {
        keyword: RESERVED_WORDS,
        built_in: BUILT_INS,
        literal: LITERALS,
        type: TYPES
      };

      const OPERATORS = {
        scope: "operator",
        match: '[\+\-\=\%\/\*\^\|\&|\!\(\)\{\}\[\\]]',
      }

      const STRING = {
        scope: 'string',
        contains: [ hljs.BACKSLASH_ESCAPE ],
        variants: [
          hljs.APOS_STRING_MODE,
          hljs.QUOTE_STRING_MODE
        ]
      };

      const NUMBER = {
        scope: 'number',
        relevance: 0,
        variants: [
          { // int
            begin: '[0-9]+',
          },
          { // flt
            begin: '[0-9]+\\.[0-9]+[f]?',
          },
        ]
      };

      const COMMENT = hljs.HASH_COMMENT_MODE;

      // e.g. def myObj
      const DEF_OBJ = {
        match: [
          `def`, SPACES, ID//ACCESSIBLE_ID,
        ],
        keywords: KEYWORDS,
        scope: {
          1: "keyword",
          3: "title.class"
        },
      };

      // e.g. (args1 type, args2 type)
      const PARAM = {
        match: [
          ID, SPACES, ID,
        ],
        keywords: KEYWORDS,
        scope: {
          1: 'variables',
          3: 'title.class',
        }
      };
      const PARAMS = {
        variants: [
          {
            begin: /\(\s*\)/,
            skip: true,
            contains: [ OPERATORS ],
          },
          {
            begin: /\(/,
            end: /\)/,
            //excludeEnd: true,
            //excludeBegin: true,
            keywords: KEYWORDS,
            contains: [
              PARAM, STRING, OPERATORS, NUMBER,
            ],
          }
        ]
      };

      // e.g. main(args1 type, args2 type) retType
      const DEF_FUNC = {
        begin: [
          ACCESSIBLE_ID, /\s*\(/
        ],
        excludeEnd: true,
        scope: {
          1: "title.function",
          2: "operator",
        },
        contains: [
          PARAMS, OPERATORS
        ],
      };

      return E => ({
            name: 'namu',
            aliases: [ 'nm' ],
            unicodeRegex: true,
            keywords: KEYWORDS,
            contains: [
              NUMBER,
              STRING,
              COMMENT,
              //DEF_VAR,
              DEF_OBJ,
              PARAMS,
              DEF_FUNC,
              OPERATORS,
            ]
          })
      })();
      hljs.registerLanguage("namu", lang);
})();