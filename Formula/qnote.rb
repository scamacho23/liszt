class Qnote < Formula
	desc "A command line note-taking software"
	homepage "https://github.com/scamacho23/quicknote"
	url "https://github.com/scamacho23/homebrew-quicknote/blob/master/qnote-v1.0.6.tar.gz"
	version "1.0.6"

	depends_on "python3"
	
	bottle :unneeded

	def install
		bin.install "qnote"
		echo "Hello, World"
	end
end
