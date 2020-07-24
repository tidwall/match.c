# match.c

A very simple pattern matcher where '*' matches on any 
number characters and '?' matches on any one character.

## Example

```c
match("*llo", 3, "hello", 5); 
match("?ello", 5, "jello", 5); 
match("h*o",  3, "hello", 5);
```

## License
match.c source code is available under the MIT [License](/LICENSE).
