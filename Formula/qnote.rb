class Qnote < Formula
	desc "A command line note-taking software"
	homepage "https://github.com/scamacho23/quicknote"
	url "https://github.com/scamacho23/homebrew-quicknote/blob/master/qnote-v1.0.6.tar.gz"
	sha256 "97cfb69948f11de2b93ec3e8653a90ad0c920eb582377543ad7f65450ce43fe7"
	version "1.0.6"

	depends_on "python3"
	
	bottle :unneeded

	def install
		bin.install "qnote"
		echo "Hello, World"
	end
end
