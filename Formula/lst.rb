class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.2.tar.gz"
  license "GNU GPL v3"
  version "1.1.2"

  def install
    system "./configure"
    system "make", "install"
  end

  test do
    system "#{bin}/lst", "-h"
  end
end
