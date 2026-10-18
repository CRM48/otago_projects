"""Small smoke tests for the COSC343 Raj agents. Run from game_playing_ai/."""
from pathlib import Path
import importlib.util

ROOT = Path(__file__).resolve().parent


def load_module(path):
    spec = importlib.util.spec_from_file_location(path.stem + "_test", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def check(name, test):
    try:
        test()
        print(f"PASS: {name}")
        return True
    except Exception as error:
        print(f"FAIL: {name} ({error})")
        return False


def search_bid():
    module = load_module(ROOT / "search_agent" / "my_agent.py")
    agent = module.RajAgent(item_values=(-2, -1, 1, 2, 3, 4), card_values=(1, 2, 3, 4, 5, 6))
    hand = (2, 5)
    # Current item, future items, our hand, bank, opponent's hand.
    bid = agent.AgentFunction((3, (1,), hand, 0, (3, 6)))
    assert bid in hand, f"Invalid bid: {bid}"


def learning_bid():
    module = load_module(ROOT / "q_learning" / "myrl_agent.py")
    agent = module.RajAgent(item_values=(-2, -1, 1, 2, 3, 4), card_values=(1, 2, 3, 4, 5, 6))
    model_file = ROOT / "q_learning" / "saved_myrl_agent.pkl"
    assert model_file.exists(), "Trained model not found"
    # Only load your own trusted saved model; pickle files can execute code.
    agent.load(str(model_file))
    assert len(agent.Q) > 0, "Saved Q-table is empty"
    hand = (1, 4, 6)
    bid = agent.AgentFunction((2, (-1, 3), hand, 0, (1, 3, 5), (2, 4, 6)))
    assert bid in hand, f"Invalid bid: {bid}"


if __name__ == "__main__":
    results = [
        check("Search agent returns a legal bid", search_bid),
        check("Saved Q-learning agent loads and returns a legal bid", learning_bid),
    ]
    print(f"\n{sum(results)}/{len(results)} tests passed")
    raise SystemExit(0 if all(results) else 1)
