sudo apt update -y
sudo apt install -y  gcc-multilib clang
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
source "$HOME/.nvm/nvm.sh"  # This loads nvm
nvm install node
npm install -g yarn
curl -sSf https://rye-up.com/get | RYE_INSTALL_OPTION="--yes" bash
echo "export NVM_DIR=\"/root/.nvm\"" >> /etc/profile.d/docker
echo "source \"/root/.rye/env\"" >> /etc/profile.d/docker
echo "source \"/root/.nvm/nvm.sh\"" >> /etc/profile.d/docker
