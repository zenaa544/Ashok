set -e

OPENSSL_VERSION="3.0.9"
PYTHON_VERSION="3.6.15"
INSTALL_DIR="/home/admin/ashok/test_manual"
BUILD_DIR="${INSTALL_DIR}/build"
PREFIX_DIR="${INSTALL_DIR}/python3.6"
VENV_DIR="${INSTALL_DIR}/env32"
CWD=$(pwd)

Create directories
mkdir -p $BUILD_DIR $PREFIX_DIR $VENV_DIR

Install necessary packages
sudo yum install -y epel-release
sudo yum install -y gcc gcc-c++.i686 make openssl-devel openssl-devel.i686 libffi-devel.i686 \
glibc-devel.i686 libgcc.i686 zlib-devel.i686 bzip2-devel.i686 \
sqlite-devel.i686

Step 1: Install Rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
rustup target add i686-unknown-linux-gnu

Step 2: Download and Install OpenSSL 32-bit
cd $BUILD_DIR
curl -O https://www.openssl.org/source/openssl-${OPENSSL_VERSION}.tar.gz
tar xvf openssl-${OPENSSL_VERSION}.tar.gz
cd openssl-${OPENSSL_VERSION}
CC="gcc -m32" ./config no-shared linux-generic32 no-ssl2 no-ssl3 -fPIC --prefix=${PREFIX_DIR}/openssl
make clean
make -j$(nproc)
make install

Verify OpenSSL installation
${PREFIX_DIR}/openssl/bin/openssl version

Step 3: Build and Install Python 32-bit
cd $BUILD_DIR
wget https://www.python.org/ftp/python/$PYTHON_VERSION/Python-$PYTHON_VERSION.tgz
tar -xzf Python-$PYTHON_VERSION.tgz
cd Python-$PYTHON_VERSION

Set environment variables for OpenSSL
export PKG_CONFIG_PATH="${PREFIX_DIR}/openssl/lib/pkgconfig:/usr/lib/pkgconfig::/usr/lib/i386-linux-gnu/pkgconfig"
export CFLAGS="-m32 -I${PREFIX_DIR}/openssl/include -I/usr/include -I/usr/include/libffi"
export LDFLAGS="m32 -L${PREFIX_DIR}/openssl/lib -L/usr/lib  -L/usr/lib/i386-linux-gnu"
export LD_LIBRARY_PATH="${PREFIX_DIR}/openssl/lib:/usr/lib:/usr/lib/i386-linux-gnu"

./configure --prefix=$PREFIX_DIR --with-openssl=${PREFIX_DIR}/openssl --enable-optimizations
make -j$(nproc)
make altinstall

Verify SSL support in Python
$PREFIX_DIR/bin/python3.6 -m ensurepip --upgrade
$PREFIX_DIR/bin/python3.6 -c "import ssl; print(ssl.OPENSSL_VERSION)"

Step 4: Create virtual environment
cd $INSTALL_DIR
$PREFIX_DIR/bin/python3.6 -m venv $VENV_DIR
source $VENV_DIR/bin/activate

Step 5: Upgrade pip and install necessary packages
pip install --upgrade pip setuptools wheel

Step 6: Set PKG_CONFIG_PATH to include OpenSSL and libffi
export PKG_CONFIG_PATH="${PREFIX_DIR}/openssl/lib/pkgconfig:/usr/lib/pkgconfig:/usr/lib/i386-linux-gnu/pkgconfig"
export CFLAGS="-m32 -I${PREFIX_DIR}/openssl/include -I/usr/include -I/usr/include/libffi"
export LDFLAGS="-m32 -L${PREFIX_DIR}/openssl/lib -L/usr/lib -L/usr/lib64 -L/usr/lib/i386-linux-gnu"
export LD_LIBRARY_PATH="${PREFIX_DIR}/openssl/lib:/usr/lib:/usr/lib/i386-linux-gnu:/usr/lib64"

Step 7: Install cffi
pip install cffi

Step 8: Build cryptography wheel
export CARGO_BUILD_TARGET=i686-unknown-linux-gnu
export OPENSSL_DIR="${PREFIX_DIR}/openssl"
export CFLAGS="-m32 -I${OPENSSL_DIR}/include -I${PREFIX_DIR}/include -I${PREFIX_DIR}/openssl/include -I/usr/include -I/usr/include/libffi"
export LDFLAGS="-m32 -L${OPENSSL_DIR}/lib -L${PREFIX_DIR}/lib -L{PREFIX_DIR}/openssl/lib -L/usr/lib/i386-linux-gnu -L/usr/lib -L/usr/lib64"
export LD_LIBRARY_PATH="${OPENSSL_DIR}/lib:${PREFIX_DIR}/lib:/usr/lib:/usr/lib64:${PREFIX_DIR}/openssl/lib:/usr/lib/i386-linux-gnu"
export PYO3_CROSS_LIB_DIR=${OPENSSL_DIR}/openssl/lib

pip wheel --no-cache-dir --no-binary :all: cryptography==38.0.4

Clean up
deactivate
cd $CWD
