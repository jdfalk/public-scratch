#!/bin/bash
##
## This will setup your mac for dev work.
##

echo "Welcome to the mac setup script. This was created to simplify initial setup."


DEBUG=0

# Install command line tools
if $DEBUG; then
	echo "Installing command line tools"
fi

xcode-select --install
if [ $? -eq 0 ]
then
	echo "Successfully installed command line tools"
else
	echo "Failed to install command line tools" >&2
fi


if [ ! -d /Applications/iterm2.app ]; then
	curl -L https://iterm2.com/downloads/stable/latest -o /Applications/iterm2.zip
	unzip /Applications/iterm2.zip
	rm /Applications/iterm2.zip
fi

# Create my GIT stuff
mkdir -p $HOME/repos/github/jdfalk
cd $HOME/repos/github/jdfalk
git clone https://github.com/jdfalk/public-scratch.git


# Install ohh my zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"


ln -s $HOME/repos/github/jdfalk/public-scratch/.istio.zsh.inc $HOME/.istio.zsh.inc
ln -s $HOME/repos/github/jdfalk/public-scratch/.kube.zsh.inc $HOME/.kube.zsh.inc
# ln -s $HOME/repos/github/jdfalk/public-scratch/.aws.zsh.inc $HOME/.aws.zsh.inc

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


if [[ $(uname -m) == 'arm64' ]]; then
	cat >> ~/.zshrc <<-EOL
		# Homebrew on M1
		export PATH="/opt/homebrew/bin:/opt/homebrew/sbin:$PATH"
	EOL
elif [[ $(uname -m) == 'x86_64' ]]; then
	cat >> ~/.zshrc <<-EOL
		# Homebrew on Intel
		export PATH="/usr/local/bin:/usr/local/sbin:$PATH"
	EOL
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
brew tap homebrew/bundle
brew tap homebrew/cask
brew tap homebrew/core
brew tap homebrew/services
# brew tap puppetlabs/puppetlabs
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
		k9s \
		kube-ps1 \
		kubectx \
		kubernetes-cli \
		mas \
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

brew cask install \
	keybase \
	lens \
	visual-studio-code

# 1Password 7
mas install 1333542190
# Microsoft Remove Desktop
mas install 1295203466
# Workspot
mas install 978894159


# Setup GIT
# git config --global user.name ""
# git config --global user.email ""


pyenv install 3.10.4
pyenv virtualenv 3.10.4 g3.10.4
pyenv global g3.10.4

cat <<'EOF' >> ~/.zshrc
export PYENV_ROOT="$HOME/.pyenv"
command -v pyenv >/dev/null || export PATH="$PYENV_ROOT/bin:$PATH"
eval "$(pyenv init -)"
EOF


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

