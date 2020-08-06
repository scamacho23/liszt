class Qnote < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-quicknote"
  url "https://github.com/scamacho23/homebrew-quicknote/archive/v1.0.16.tar.gz"
  sha256 "01c8049523e85fbb174771fff20fb56edcfc26f1e29c565396df9cb2ad59704a"
  license "GNU GPL v3"
  version "1.0.6"


  def install
    bin.install "qnote"
  end

end
