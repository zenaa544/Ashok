import re
from urllib.parse import unquote_plus

class URL:
    # Regex to validate URL and capture groups:
    url_regex = re.compile(
        r'^(https?|ftp)://'                          # scheme
        r'([a-zA-Z0-9\-\.]+|\[[0-9a-fA-F:]+\]|\d{1,3}(?:\.\d{1,3}){3})'  # host (domain or IPv6 or IPv4)
        r'(?::(\d+))?'                               # port (optional)
        r'(\/[^\s?#]*)?'                             # path (optional)
        r'(\?[^\s#]*)?'                              # query (optional)
        r'(#[^\s]*)?$',                              # fragment (optional)
        re.IGNORECASE
    )

    def __init__(self, url: str):
        self.url = url
        if not self.validate():
            raise ValueError("Invalid URL format")
        self._parse()

    def validate(self):
        return bool(self.url_regex.match(self.url))

    def _parse(self):
        match = self.url_regex.match(self.url)
        self.scheme = match.group(1)
        self.host = match.group(2)
        self.port = int(match.group(3)) if match.group(3) else None
        self.path = match.group(4) if match.group(4) else ''
        self.query = match.group(5)[1:] if match.group(5) else ''  # remove leading '?'
        self.fragment = match.group(6)[1:] if match.group(6) else ''  # remove leading '#'
        self.query_params = self._parse_query_params(self.query)

    def _parse_query_params(self, query):
        params = {}
        if not query:
            return params
        pairs = query.split('&')
        for pair in pairs:
            if not pair:
                continue
            if '=' in pair:
                key, value = pair.split('=', 1)
                params[unquote_plus(key)] = unquote_plus(value)
            else:
                params[unquote_plus(pair)] = ''
        return params

    def set_url(self, new_url: str):
        self.url = new_url
        if not self.validate():
            raise ValueError("Invalid URL format")
        self._parse()

    def get_scheme(self): return self.scheme
    def get_host(self): return self.host
    def get_port(self): return self.port
    def get_path(self): return self.path
    def get_query(self): return self.query
    def get_fragment(self): return self.fragment
    def get_query_params(self): return self.query_params
    def get_url(self): return self.url

# Example usage:
if __name__ == "__main__":
    try:
        url = URL("https://example.com:8080/path/to/resource?foo=bar&baz=qux#frag")
        print("Scheme:", url.get_scheme())
        print("Host:", url.get_host())
        print("Port:", url.get_port())
        print("Path:", url.get_path())
        print("Query:", url.get_query())
        print("Fragment:", url.get_fragment())
        print("Query Params:", url.get_query_params())

        url.set_url("ftp://192.168.0.1/resource?x=1&y=2")
        print("\nNew URL Host:", url.get_host())
        print("New URL Query Params:", url.get_query_params())
    except ValueError as e:
        print("Error:", e)
