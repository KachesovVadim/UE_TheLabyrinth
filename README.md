# TheLabyrinth

Проект на Unreal Engine 5.2.1, созданный за 7 дней с применением bp&c++. Совместно разработан с моим другом Render - https://t.me/Render_Official.
Геймплейный ролик – https://youtu.be/pMPQyztgltk

Процесс разработки:
Первым делом была реализована генерация лабиринта. Backtracking алгоритм генерации лабиринта; спавн стен были написан мной полностью с нуля. Эта часть реализована на c++.
Далее Render занялся созданием 3д моделей для всей игры, локацией.

Лабиринт с кастомными стенами в вьюпорте и в игре.

![Снимок экрана 2023-09-07 003412](https://github.com/KachesovVadim/UE_TheLabyrinth/assets/142095950/b52d59b3-dfcf-4b44-ab3f-35439e9794f6)
![Снимок экрана 2023-09-07 003538](https://github.com/KachesovVadim/UE_TheLabyrinth/assets/142095950/9c257546-fada-4df4-a153-f974c1e4adab)

После стен я занялся механиками выигрыша и проигрыша:
Выиграть можно успев до истечения времени нажать кнопку в конце лабиринтов или же застрелив авантюриста.
Проиграть, если не имея пистолет встретить авантюриста, или не успеть дойти до кнопки.

Добавил авантюриста на уровень, звуки, покачивание камеры.

![Снимок экрана 2023-09-07 004216](https://github.com/KachesovVadim/UE_TheLabyrinth/assets/142095950/03a0f60f-39f6-4d51-b681-8748be58409b)

В последнюю очередь была реализована система диалогов. За нее отвечал Render.

![image](https://github.com/KachesovVadim/UE_TheLabyrinth/assets/142095950/5181db2c-07d8-421e-a951-a08de24d685d)

Для синхронизации прогресса мы использовали Git. Проект был создан для подтверждения навыков владения с++, практики командной работы.


Управление:

WASD – перемещение

Space – действие
