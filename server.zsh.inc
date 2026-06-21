# file: server.zsh.inc
# version: 1.0.0
# guid: b7c8d9e0-f1a2-3b4c-5d6e-7f8a9b0c1d2e
# last-edited: 2026-06-21
#
# Common shell config for headless servers (Lenovo fleet + RPi Tang nodes).
# Sourced from ~/.zshrc (or ~/.bashrc) on each server.
# Repo: https://github.com/falkcorp/public-scratch

# Never open a pager — output goes to the terminal directly.
export PAGER=cat
export MANPAGER=cat
export GIT_PAGER=cat

# Better defaults when something still invokes less.
export LESS="-FRX"

# Sane editor.
export EDITOR=vim
export VISUAL=vim

# Colour and human-readable output by default.
alias ls='ls --color=auto'
alias ll='ls -lhF --color=auto'
alias la='ls -lahF --color=auto'
alias grep='grep --color=auto'
alias df='df -h'
alias du='du -sh'

# Git shortcuts.
alias gs='git status'
alias gl='git log --oneline --graph --decorate -20'

# Kubernetes shortcuts (no-op if kubectl not installed).
if command -v kubectl &>/dev/null; then
  alias k='kubectl'
  alias kgp='kubectl get pods'
  alias kgs='kubectl get svc'
fi
