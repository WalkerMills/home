set number
syntax on
highlight Comment ctermfg=gray
highlight Constant ctermfg=blue
highlight Identifier ctermfg=white
highlight Statement ctermfg=red 
highlight Function ctermfg=cyan
highlight Define ctermfg=cyan
highlight PreProc ctermfg=cyan
highlight String cterm=none ctermfg=green
highlight Type cterm=bold ctermfg=green 
highlight Special ctermfg=yellow
highlight Include ctermfg=red

filetype plugin on
set ofu=syntaxcomplete#Complete

set completeopt=longest,menuone
inoremap <expr> <CR> pumvisible() ? "\<C-y>" : "\<C-g>u\<CR>"
inoremap <expr> <C-n> pumvisible() ? '<C-n>' :
  \ '<C-n><C-r>=pumvisible() ? "\<lt>Down>" : ""<CR>'

inoremap <expr> <M-,> pumvisible() ? '<C-n>' :
  \ '<C-x><C-o><C-n><C-p><C-r>=pumvisible() ? "\<lt>Down>" : ""<CR>'
