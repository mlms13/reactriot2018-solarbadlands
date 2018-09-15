type url = string;

type commit = {
  sha: string,
  url: url
};

type branch = {
  name: string,
  commit: commit,
  protected: bool,
  protectionUrl: url,
};

type t = {
  owner: string,
  slug: string,
  branches: list(branch)
};
