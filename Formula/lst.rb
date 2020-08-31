class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.6.tar.gz"
  sha256 "55f90361d00e5d579dadc44885b7cb984ece55dbe6ec66cb771174c7e6bf2adc"
  license "GNU GPL v3"
  version "1.1.6"

  depends_on "cmake" => :build

  def install
    system "cmake", "source"
    system "make"
    # system "make", "install", "PREFIX=#{prefix}"
    bin.install "lst"
  end

  test do
    system "#{bin}/lst", "-h"
  end
end
