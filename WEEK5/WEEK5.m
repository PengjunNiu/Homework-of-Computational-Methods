n = input('请输入Hilbert矩阵的大小：');
hilbertMatrix = hilb(n);
vector = ones(n, 1);

[L, U, P] = lu(hilbertMatrix);
y = P * vector;
solution = U \ (L \ y);

disp('Solution:');
for i = 1:n
    disp(['x', num2str(i), ' = ', num2str(solution(i))]);
end