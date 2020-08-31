#!/bin/bash
##
## This will setup your mac for dev work.
##

echo "Welcome to the mac setup script. This was created to simplify initial setup."


# Install command line tools
xcode-select --install

if [ $? -eq 0 ]
then
  echo "Successfully installed command line tools"
else
  echo "FaIled to install command line tools" >&2
fi


# Setup brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
brew docter
brew update

# Install brew taps
brew tap argoproj/tap
brew tap aws/tap
brew tap boz/repo
brew tap go-delve/delve
brew tap homebrew/cask
brew tap homebrew/core
brew tap puppetlabs/puppetlabs
brew update

# Install basic software
brew install \
    awscli \
    azure-cli \
    bash-completion \
    coreutils \
    fortune \
    gnu-sed \
    gnu-tar \
    gnupg \
    go \
    helm \
    iperf3 \
    istioctl \
    jq \
    kubectx \
    kubernetes-cli \
    kube-ps1 \
    openssl \
    packer \
    prometheus \
    pyenv \
    pyenv-virtualenv \
    rclone \
    stern \
    terraform \
    terraform-docs \
    terragrunt \
    zsh-syntax-highlighting \
    zsh-autosuggestions 

brew cask install puppetlabs/puppet/pdk

# Setup GIT
# git config --global user.name ""
# git config --global user.email ""

# Create my GIT stuff
mkdir -p $HOME/repos/github/jdfalk
cd $HOME/repos/github/jdfalk
git clone https://github.com/jdfalk/public-scratch.git


# Install ohh my zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"


cat <<'EOF' >> ~/.zshrc
if [ -f ~/.kube.zsh.inc ]; then
    source ~/.kube.zsh.inc
fi

if [ -f ~/.istio.zsh.inc ]; then
    source ~/.istio.zsh.inc
fi

if [ -f ~/.aws.zshrc.inc ]; then
    source ~/.aws.zshrc.inc
fi
EOF


ln -s $HOME/repos/github/jdfalk/public-scratch/.istio.zsh.inc $HOME/.istio.zsh.inc
ln -s $HOME/repos/github/jdfalk/public-scratch/.kube.zsh.inc $HOME/.kube.zsh.inc


echo "Remember to install vscode and settings sync"

## Plugins

# Install Krew
echo "Installing Krew..."

(
  set -x; cd "$(mktemp -d)" &&
  curl -fsSLO "https://github.com/kubernetes-sigs/krew/releases/latest/download/krew.{tar.gz,yaml}" &&
  tar zxvf krew.tar.gz &&
  KREW=./krew-"$(uname | tr '[:upper:]' '[:lower:]')_amd64" &&
  "$KREW" install --manifest=krew.yaml --archive=krew.tar.gz &&
  "$KREW" update
)

