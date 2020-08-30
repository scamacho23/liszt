class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.5.tar.gz"
  license "GNU GPL v3"
  version "1.1.5"

  def install
    system "aclocal"
    system "autoconf"
    system "automake --add-missing"
    system "./configure", "--prefix=#{prefix}"
    system "make"
    system "make", "install"
  end

  test do
    system "lst", "-h"
  end
end
