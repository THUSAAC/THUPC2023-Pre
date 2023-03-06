{{ self.title() }}

{{ s('background') }}

本来这题的题面和《喵了个喵》有关的。但是听说有人嫌题面长，就少说点好了。

{{ s('description') }}

给定一个长为 $4n$ 的序列，其中 $1\sim n$ 各出现 $4$ 次。问是否能够将其划分为两个相等的子序列。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个正整数 $n$。

第二行 $4n$ 个正整数，表示序列。保证 $1\sim n$ 各出现 $4$ 次。

{{ s('output format') }}

{{ self.output_file() }}

如果不能划分为两个相等的子序列，输出一行 `No`。

否则第一行输出 `Yes`。第二行输出一个长为 $4n$ 的 `01` 串。其中第 $i$ 位表示原序列的第 $i$ 个数被划分到第几个子序列。你需要保证你划分出来的两个子序列完全相等。

{{ s('sample', ) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

两个子序列均为 $(1,2,1,2)$。

{{ s('subtasks') }}

保证 $1\le n \le 5\times10^4$。

保证序列中 $1\sim n$ 各出现 $4$ 次。

{{ s('scoring') }}

你的输出的第一行需要与标准答案一致。若为 `Yes`，输出任意一种合法的划分均算正确。