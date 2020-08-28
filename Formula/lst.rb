class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.0.20.tar.gz"
  sha256 "bd5f661f4b0fa04d082562dbfa94931cf2ebd5b8a32e15ca22958216b9580754"
  license "GNU GPL v3"
  version "1.0.20"

  def install
    bin.install "lst"
  end

end
