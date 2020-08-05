class Qnote < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-quicknote"
  url "https://github.com/scamacho23/homebrew-quicknote/archive/v1.0.8.tar.gz"
  sha256 "4e578aeb0b2eeed06311ada45f5f90454b0add2d0b658d168947cc0c67911945"
  license "GNU GPL v3"
  version "1.0.6"


  def install
    bin.install "qnote"
  end

end
