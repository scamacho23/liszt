class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.6.tar.gz"
  license "GNU GPL v3"
  version "1.1.6"

  depends_on "cmake" => :build

  def install
    system "cmake", "source"
    system "make"
    system "make", "install"
  end

  test do
    system "lst", "-h"
  end
end
