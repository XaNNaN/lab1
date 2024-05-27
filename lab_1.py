import networkx as nx
import matplotlib.pyplot as plt
import math
from icecream import ic

def build_prism_graph():
    def dist(p1, p2):
        return math.hypot(p2[0] - p1[0], p2[1] - p1[1])
    
    def dists(points):
        result = []
        # Calculating edges length
        for i, el in enumerate(points):
            result += [(dist(p1, p2), p1[2], p2[2]) for p1, p2 in zip(points[:-i], points[i:])]
            ic([(dist(p1, p2), p1[2], p2[2]) for p1, p2 in zip(points[:-i], points[i:])])
        return result
    

    G = nx.Graph()


    # Coordinates for fully connected graph
    coordinates = [
                   (1, 0,  'A'),
                   (0.5, -1 *math.sqrt(3) / 2, 'B'),
                   (-0.5, -1 *math.sqrt(3) / 2, 'C'),
                   (-1, 0, 'D'), # D
                   (-0.5, math.sqrt(3) / 2, 'E'),
                   (0.5, math.sqrt(3) / 2, 'F'),
                   ]
    
    
    calculated_dists = dists(coordinates)
    ic(calculated_dists)

    
    for edge in calculated_dists:
        G.add_edge(edge[1], edge[2], weight=edge[0])

    pos = nx.circular_layout(G)
    ic(nx.circular_layout(G))
    for el in coordinates:
        pos[el[2]] = [el[0], el[1]]

    return G, pos

def find_mst(G):
    # Используем алгоритм Прима для нахождения остовного дерева
    mst = nx.minimum_spanning_tree(G, algorithm='prim')
    return mst

def main():
    G, pos = build_prism_graph()
    mst = find_mst(G)
    
    # Выводим остовное дерево
    ic("Рёбра остовного дерева:")
    ic(mst.edges())
    # for edge in mst.edges():
    #     print(edge)
    
    # Отображаем граф и остовное дерево
    plt.figure(figsize=(12, 6))
    
    plt.subplot(121)
    labels = list(nx.get_edge_attributes(G,'weight').values())
    ic(labels)
    nx.draw(G, with_labels=True, pos=pos, node_color='lightblue', node_size=500, font_size=16, edge_color=labels,  edge_cmap=plt.cm.Blues_r, width=2)
    plt.title('Исходный граф правильного шестиугольника')
    
    plt.subplot(122)
    labels = list(nx.get_edge_attributes(mst,'weight').values())
    nx.draw(mst, with_labels=True, node_color='lightgreen', node_size=500, font_size=16, pos=pos, edge_color='green',  edge_cmap=plt.cm.Greens_r, width=2)
    plt.title('Остовное дерево (MST)')
    
    plt.show()

if __name__ == '__main__':
    main()
