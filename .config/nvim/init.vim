" This line makes pacman-installed global Arch Linux vim packages work.
source /usr/share/nvim/archlinux.vim

call plug#begin()

Plug 'vim-airline/vim-airline'
Plug 'dylanaraps/wal.vim'
Plug 'ap/vim-css-color'
Plug 'vim-python/python-syntax'
Plug 'scrooloose/nerdtree'                        
Plug 'tiagofumo/vim-nerdtree-syntax-highlight'
Plug 'davidhalter/jedi-vim'

call plug#end()
syntax enable

let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ''
let g:airline#extensions#tabline#left_alt_sep = ''
let g:airline#extensions#tabline#formatter = 'unique_tail'
let g:airline_left_sep=''
let g:airline_right_sep=''
let g:python_highlight_all = 1

" Python
let g:jedi#environment_path = "/usr/bin/python3.9"
let g:jedi#completions_enabled = 1

set number
set path+=**
set t_Co=256
set mouse=nicr
set mouse=a
set guicursor=

colorscheme wal


