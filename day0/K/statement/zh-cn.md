{{ self.title() }}

{{ s('description') }}

你有若干个 $[1,n]$ 内的正整数：对于 $1 \le i \le n$，你有 $a_i$ 个整数 $i$。设 $S = \sum_{i=1}^n a_i$。

对于一个序列 $p_1,p_2,\cdots,p_l$，定义其众数 $\text{maj}(p_1,p_2,\cdots,p_l)$ 为出现次数最多的数。若有多个数出现次数最多，则其中最大的数为其众数。

现在你需要把这 $S$ 个数排成一个序列 $b_1,b_2,\cdots,b_S$，使得 $\sum_{i=1}^S \text{maj}(b_1,b_2,\cdots,b_i)$ 最大。输出该最大值。

{{ s('input format') }}

{{ self.input_file() }}

第一行一个整数 $n$，表示值域。

接下来一行 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，表示每种数的个数。

{{ s('output format') }}

{{ self.output_file() }}

输出一行一个正整数表示 $\sum_{i=1}^S \text{maj}(b_1,b_2,\cdots,b_i)$ 的最大值。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ self.title_sample_description() }}

一个达到最大值的序列为 $(3,2,3,1,2,2)$。

{{ s('数据范围') }}

对于所有测试数据，$1 \le n \leq 10^5$，$1 \le a_1,a_2,\cdots,a_n \le 10^5$。