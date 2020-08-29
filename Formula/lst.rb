class Lst < Formula
  desc "Software to save command line arguments as 'memories'"
  homepage "https://github.com/scamacho23/homebrew-liszt"
  url "https://github.com/scamacho23/homebrew-liszt/archive/v1.1.0.tar.gz"
  sha256 "347fafaf67e48f0e2e528c0e7aebe503a3bdf8044af8b24ca31574d51147fe65"
  license "GNU GPL v3"
  version "1.1.0"

  def install
    bin.install "lst"
  end

end
