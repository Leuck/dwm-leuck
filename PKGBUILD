# $Id$
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.1
pkgrel=1
pkgdesc="A dynamic window manager for X - leuck's config"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
	config.h
	dwm.desktop
	dwmstatus.c
	dwminit.sh)
md5sums=('f0b6b1093b7207f89c2a90b848c008ec'
         'e3ac8c4c5e4e5cccc69e7a781c5ff590'
         'e8c591b66e4e8b6a7378c741b3c62bcc'
         '2bda0b7f6a34a57361532d421d04a58f'
         '993feba3a8d4f790e3483f0a84c75c44')

prepare() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  cp $srcdir/dwmstatus.c dwmstatus.c
}

build() {
  cd $srcdir/$pkgname-$pkgver
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
  gcc -o dwmstatus dwmstatus.c
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
  install -m755 -D dwmstatus $pkgdir/usr/bin/dwmstatus
  install -m755 -D $srcdir/dwminit.sh $pkgdir/usr/local/bin/dwminit.sh
}
