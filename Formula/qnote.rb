class Qnote < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-quicknote"
  url "https://github.com/scamacho23/homebrew-quicknote/archive/v1.0.6.tar.gz"
  sha256 "f519eb3b14d698b87e74235a478e2b4d3d88eb7681738c805790bcfe23e58878"
  license "GNU GPL v3"
  version "1.0.6"


  def install
    bin.install "qnote"
  end

  test do
    echo "hello there"
  end
end
